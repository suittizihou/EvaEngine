#include "VRMModelLoader.h"

#include <memory>
#include <DirectXTex.h>

#include "../../../Plugin/StreamReader.h"
#include "../../../../GameSystemBase/DataBase/ModelDataBase/ModelDataBase.h"

using namespace DirectX;
using namespace std;

ModelData::Model VRMModelLoader::LoadModel(const std::string fileName)
{
    // モデルデータの読み込み
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

    LoadModelGeometry(document, glbResourceReader);
    LoadModelMaterial(document, glbResourceReader);

    return m_Model;
}

ModelData::Model VRMModelLoader::MakeModelDataMemory(const ModelData::Model& model)
{


    ModelData::Model tempModel = model;
    MakeModelGeometry(tempModel);
    MakeModelMaterial(tempModel);
    //ModelApp::Instance().CreateConstantBuffer(tempModel);
    //ModelApp::Instance().CreateSampler(tempModel);
    return tempModel;
}

void VRMModelLoader::LoadModelGeometry(const Microsoft::glTF::Document& doc, std::shared_ptr<Microsoft::glTF::GLTFResourceReader> reader)
{
    using namespace Microsoft::glTF;
    for (const auto& mesh : doc.meshes.Elements())
    {
        for (const auto& meshPrimitive : mesh.primitives)
        {
            ModelData::ModelMesh mesh;

            // 頂点位置情報アクセッサの取得
            auto& idPos = meshPrimitive.GetAttributeAccessorId(ACCESSOR_POSITION);
            auto& accPos = doc.accessors.Get(idPos);
            // 法線情報アクセッサの取得
            auto& idNrm = meshPrimitive.GetAttributeAccessorId(ACCESSOR_NORMAL);
            auto& accNrm = doc.accessors.Get(idNrm);
            // テクスチャ座標情報アクセッサの取得
            auto& idUV = meshPrimitive.GetAttributeAccessorId(ACCESSOR_TEXCOORD_0);
            auto& accUV = doc.accessors.Get(idUV);
            // 頂点インデックス用アクセッサの取得
            auto& idIndex = meshPrimitive.indicesAccessorId;
            auto& accIndex = doc.accessors.Get(idIndex);

            // アクセッサからデータ列を取得
            auto vertPos = reader->ReadBinaryData<float>(doc, accPos);
            auto vertNrm = reader->ReadBinaryData<float>(doc, accNrm);
            auto vertUV = reader->ReadBinaryData<float>(doc, accUV);

            //auto vertexCount = accPos.count;
            //for (uint32_t i = 0; i < vertexCount; ++i)
            //{
            //    // 頂点データの構築
            //    int vid0 = 3 * i, vid1 = 3 * i + 1, vid2 = 3 * i + 2;
            //    int tid0 = 2 * i, tid1 = 2 * i + 1;
            //    mesh.m_Vertices.emplace_back(
            //        ModelData::VertexData{
            //          XMFLOAT3(vertPos[vid0], vertPos[vid1],vertPos[vid2]),
            //          XMFLOAT3(vertNrm[vid0], vertNrm[vid1],vertNrm[vid2]),
            //          XMFLOAT2(vertUV[tid0],vertUV[tid1])
            //        }
            //    );
            //}

            // インデックスデータ
            mesh.m_Indices = reader->ReadBinaryData<uint32_t>(doc, accIndex);
            // マテリアルIDを登録
            mesh.m_MaterialIndex = int(doc.materials.GetIndex(meshPrimitive.materialId));

            m_Model.meshes[""].push_back(mesh);
        }
    }
}

void VRMModelLoader::MakeModelGeometry(ModelData::Model& model)
{
    //for (auto& meshs : model.meshes) {
    //    for (auto& mesh : meshs.second) {
    //        auto vbSize = UINT(sizeof(ModelData::VertexData) * mesh.m_Vertices.size());
    //        auto ibSize = UINT(sizeof(uint32_t) * mesh.m_Indices.size());
    //        auto vb = ModelApp::Instance().CreateBuffer(vbSize, mesh.m_Vertices.data());
    //        D3D12_VERTEX_BUFFER_VIEW vbView;
    //        vbView.BufferLocation = vb->GetGPUVirtualAddress();
    //        vbView.SizeInBytes = vbSize;
    //        vbView.StrideInBytes = sizeof(ModelData::VertexData);
    //        mesh.m_VertexBuffer.buffer = vb;
    //        mesh.m_VertexBuffer.vertexView = vbView;

    //        auto ib = ModelApp::Instance().CreateBuffer(ibSize, mesh.m_Indices.data());
    //        D3D12_INDEX_BUFFER_VIEW ibView;
    //        ibView.BufferLocation = ib->GetGPUVirtualAddress();
    //        ibView.Format = DXGI_FORMAT_R32_UINT;
    //        ibView.SizeInBytes = ibSize;
    //        mesh.m_IndexBuffer.buffer = ib;
    //        mesh.m_IndexBuffer.indexView = ibView;

    //        mesh.vertexCount = UINT(mesh.m_Vertices.size());
    //        mesh.indexCount = UINT(mesh.m_Indices.size());
    //    }
    //}
}

void VRMModelLoader::LoadModelMaterial(const Microsoft::glTF::Document& doc, std::shared_ptr<Microsoft::glTF::GLTFResourceReader> reader)
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

        ModelData::Material material{};
        material.m_ImageData = imageData;
        material.m_AlphaMode = m.alphaMode;

        m_Model.materials[""].push_back(material);
    }
}

void VRMModelLoader::MakeModelMaterial(ModelData::Model& model)
{
    //int textureIndex = 0;

    //for (auto& materials : model.materials) {
    //    for (auto& material : materials.second) {
    //        auto texObj = ModelApp::Instance().CreateTextureFromMemory(material.m_ImageData);
    //        material.texture = texObj.texture;

    //        // シェーダーリソースビューの生成.
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
