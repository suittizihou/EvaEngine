#include "VRMModelLoader.h"

#include <memory>
#include <DirectXTex.h>

#include "../../../Plugin/StreamReader.h"
#include "../../../../GameSystemBase/DataBase/ModelDataBase/ModelDataBase.h"
#include "../../../BufferCreate/BufferCreate.h"

using namespace DirectX;
using namespace std;
using namespace EvaEngine;
using namespace EvaEngine::Internal;

void VRMModelLoader::LoadModel(const char* fileName, std::shared_ptr<EvaEngine::ModelData>& model)
{
    // ���f���f�[�^�̓ǂݍ���
    auto modelFilePath = experimental::filesystem::path(fileName);
    if (modelFilePath.is_relative())
    {
        auto current = experimental::filesystem::current_path();
        current /= modelFilePath;
        current.swap(modelFilePath);
    }
    auto reader = make_unique<StreamReader>(modelFilePath.parent_path());
    auto glbStream = reader->GetInputStream(modelFilePath.filename().u8string());
    auto glbResourceReader = make_shared<Microsoft::glTF::GLBResourceReader>(std::move(reader), std::move(glbStream));
    auto document = Microsoft::glTF::Deserialize(glbResourceReader->GetJson());

    LoadModelGeometry(model, document, glbResourceReader);
    LoadModelMaterial(model, document, glbResourceReader);
}

std::shared_ptr<EvaEngine::ModelData> VRMModelLoader::MakeModelDataMemory(std::shared_ptr<EvaEngine::ModelData>& model)
{
    std::shared_ptr<ModelData> tempModel = model;
    MakeModelGeometry(tempModel);
    MakeModelMaterial(tempModel);
    //ModelApp::Instance().CreateConstantBuffer(tempModel);
    //ModelApp::Instance().CreateSampler(tempModel);
    return tempModel;
}

void VRMModelLoader::LoadModelGeometry(std::shared_ptr<EvaEngine::ModelData>& model, const Microsoft::glTF::Document& doc, std::shared_ptr<Microsoft::glTF::GLTFResourceReader> reader)
{
    using namespace Microsoft::glTF;
    for (const auto& mesh : doc.meshes.Elements())
    {
        for (const auto& meshPrimitive : mesh.primitives)
        {
            Mesh tempMesh{};

            // ���_�ʒu���A�N�Z�b�T�̎擾
            auto& idPos = meshPrimitive.GetAttributeAccessorId(ACCESSOR_POSITION);
            auto& accPos = doc.accessors.Get(idPos);
            // �@�����A�N�Z�b�T�̎擾
            auto& idNrm = meshPrimitive.GetAttributeAccessorId(ACCESSOR_NORMAL);
            auto& accNrm = doc.accessors.Get(idNrm);
            //// ���_�̃J���[�A�N�Z�b�T�̎擾
            //auto& idColor = meshPrimitive.GetAttributeAccessorId(ACCESSOR_COLOR_0);
            //auto& accColor = doc.accessors.Get(idColor);
            // �e�N�X�`�����W���A�N�Z�b�T�̎擾
            auto& idUV = meshPrimitive.GetAttributeAccessorId(ACCESSOR_TEXCOORD_0);
            auto& accUV = doc.accessors.Get(idUV);
            // ���_�C���f�b�N�X�p�A�N�Z�b�T�̎擾
            auto& idIndex = meshPrimitive.indicesAccessorId;
            auto& accIndex = doc.accessors.Get(idIndex);

            // �A�N�Z�b�T����f�[�^����擾
            auto vertPos = reader->ReadBinaryData<float>(doc, accPos);
            auto vertNrm = reader->ReadBinaryData<float>(doc, accNrm);
            //auto vertColor = reader->ReadBinaryData<float>(doc, accColor);
            auto vertUV = reader->ReadBinaryData<float>(doc, accUV);

            auto vertexCount = accPos.count;
            std::vector<VertexData> vertices;
            for (uint32_t i = 0; i < vertexCount; ++i)
            {
                // ���_�f�[�^�̍\�z
                int vid0 = 3 * i, vid1 = 3 * i + 1, vid2 = 3 * i + 2, vid3 = 3 * i + 3;
                int tid0 = 2 * i, tid1 = 2 * i + 1;
                vertices.emplace_back(
                    VertexData{
                      XMFLOAT3(vertPos[vid0], vertPos[vid1],vertPos[vid2]),
                      XMFLOAT3(vertNrm[vid0], vertNrm[vid1],vertNrm[vid2]),
                      XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
                      XMFLOAT2(vertUV[tid0],vertUV[tid1])
                    }
                );
            }

            // ���_�f�[�^���Z�b�g
            tempMesh.SetVertexData(vertices);
            // �C���f�b�N�X�f�[�^���Z�b�g
            tempMesh.SetIndices(reader->ReadBinaryData<uint32_t>(doc, accIndex));
            // �}�e���A��ID��o�^
            tempMesh.SetMaterialName(int(doc.materials.GetIndex(meshPrimitive.materialId)));

            model->meshes[mesh.name].push_back(tempMesh);
        }
    }
}

void VRMModelLoader::MakeModelGeometry(std::shared_ptr<ModelData>& model)
{
    size_t vertexBufferSize = sizeof(VertexData);
    for (auto& meshs : model->meshes) {
        for (auto& mesh : meshs.second) {
            // ���_�o�b�t�@�̍쐬�ƃZ�b�g
            auto vertexBuffer = BufferCreate::CreateVertexBuffer(mesh.GetVertexData(), vertexBufferSize);
            mesh.SetVertexBuffer(vertexBuffer);

            // �C���f�b�N�X�o�b�t�@�̍쐬�ƃZ�b�g
            auto indexBufferSize = UINT(sizeof(uint32_t) * mesh.GetIndices().size());
            auto indexBuffer = BufferCreate::CreateIndexBuffer(mesh.GetIndices(), indexBufferSize);
            mesh.SetIndexBuffer(indexBuffer);
        }
    }
}

void VRMModelLoader::LoadModelMaterial(std::shared_ptr<EvaEngine::ModelData>& model, const Microsoft::glTF::Document& doc, std::shared_ptr<Microsoft::glTF::GLTFResourceReader> reader)
{
    for (auto& m : doc.materials.Elements())
    {
        auto textureId = m.metallicRoughness.baseColorTexture.textureId;
        if (textureId.empty())
        {
            textureId = m.normalTexture.textureId;
        }
        auto& texture = doc.textures.Get(textureId);
        auto& image = doc.images.Get(texture.imageId);
        auto imageBufferView = doc.bufferViews.Get(image.bufferViewId);
        auto imageData = reader->ReadBinaryData<char>(doc, imageBufferView);

        Material material{};
        material.g_ImageData = imageData;
        material.g_AlphaMode = m.alphaMode;

        model->materials[m.name] = material;
    }
}

void VRMModelLoader::MakeModelMaterial(std::shared_ptr<ModelData>& model)
{
    //int textureIndex = 0;

    //for (auto& materials : model.materials) {
    //    for (auto& material : materials.second) {
    //        auto texObj = ModelApp::Instance().CreateTextureFromMemory(material.m_ImageData);
    //        material.texture = texObj.texture;

    //        // �V�F�[�_�[���\�[�X�r���[�̐���.
    //        auto descriptorIndex = ModelApp::Instance().m_SrvDescriptorBase + textureIndex;
    //        auto srvHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(
    //            model.m_HeapSrvCbv->GetCPUDescriptorHandleForHeapStart(),
    //            descriptorIndex,
    //            model.m_SrvcbvDescriptorSize);
    //        D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{};
    //        srvDesc.Texture2D.MipLevels = 1;
    //        srvDesc.Format = texObj.format;
    //        srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    //        srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    //        ModelApp::Instance().m_Device->CreateShaderResourceView(
    //            texObj.texture.Get(), &srvDesc, srvHandle);
    //        material.shaderResourceView =
    //            CD3DX12_GPU_DESCRIPTOR_HANDLE(
    //                model.m_HeapSrvCbv->GetGPUDescriptorHandleForHeapStart(),
    //                descriptorIndex,
    //                model.m_SrvcbvDescriptorSize);

    //        textureIndex++;
    //    }
    //}
}
