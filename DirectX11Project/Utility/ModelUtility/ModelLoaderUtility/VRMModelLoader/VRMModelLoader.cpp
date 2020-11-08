#include "VRMModelLoader.h"

#include <memory>
#include <DirectXTex.h>

#include "../../../Plugin/StreamReader.h"
#include "../../../../GameSystemBase/DataBase/ModelDataBase/ModelDataBase.h"
#include "../../../BufferCreate/BufferCreate.h"

using namespace DirectX;
using namespace std;

My3DLib::Model VRMModelLoader::LoadModel(const std::string fileName)
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

My3DLib::Model VRMModelLoader::MakeModelDataMemory(const My3DLib::Model& model)
{
    My3DLib::Model tempModel = model;
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
            My3DLib::Mesh mesh{};

            // 頂点位置情報アクセッサの取得
            auto& idPos = meshPrimitive.GetAttributeAccessorId(ACCESSOR_POSITION);
            auto& accPos = doc.accessors.Get(idPos);
            // 法線情報アクセッサの取得
            auto& idNrm = meshPrimitive.GetAttributeAccessorId(ACCESSOR_NORMAL);
            auto& accNrm = doc.accessors.Get(idNrm);
            //// 頂点のカラーアクセッサの取得
            //auto& idColor = meshPrimitive.GetAttributeAccessorId(ACCESSOR_COLOR_0);
            //auto& accColor = doc.accessors.Get(idColor);
            // テクスチャ座標情報アクセッサの取得
            auto& idUV = meshPrimitive.GetAttributeAccessorId(ACCESSOR_TEXCOORD_0);
            auto& accUV = doc.accessors.Get(idUV);
            // 頂点インデックス用アクセッサの取得
            auto& idIndex = meshPrimitive.indicesAccessorId;
            auto& accIndex = doc.accessors.Get(idIndex);

            // アクセッサからデータ列を取得
            auto vertPos = reader->ReadBinaryData<float>(doc, accPos);
            auto vertNrm = reader->ReadBinaryData<float>(doc, accNrm);
            //auto vertColor = reader->ReadBinaryData<float>(doc, accColor);
            auto vertUV = reader->ReadBinaryData<float>(doc, accUV);

            auto vertexCount = accPos.count;
            std::vector<My3DLib::VertexData> vertices;
            for (uint32_t i = 0; i < vertexCount; ++i)
            {
                // 頂点データの構築
                int vid0 = 3 * i, vid1 = 3 * i + 1, vid2 = 3 * i + 2, vid3 = 3 * i + 3;
                int tid0 = 2 * i, tid1 = 2 * i + 1;
                vertices.emplace_back(
                    My3DLib::VertexData{
                      XMFLOAT3(vertPos[vid0], vertPos[vid1],vertPos[vid2]),
                      XMFLOAT3(vertNrm[vid0], vertNrm[vid1],vertNrm[vid2]),
                      XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),
                      XMFLOAT2(vertUV[tid0],vertUV[tid1])
                    }
                );
            }

            // 頂点データをセット
            mesh.SetVertexData(vertices);
            // インデックスデータをセット
            mesh.SetIndices(reader->ReadBinaryData<uint32_t>(doc, accIndex));
            // マテリアルIDを登録
            mesh.SetMaterialID(int(doc.materials.GetIndex(meshPrimitive.materialId)));

            m_Model.meshes[""].push_back(mesh);
        }
    }
}

void VRMModelLoader::MakeModelGeometry(My3DLib::Model& model)
{
    size_t vertexBufferSize = sizeof(My3DLib::VertexData);
    for (auto& meshs : model.meshes) {
        for (auto& mesh : meshs.second) {
            // 頂点バッファの作成とセット
            auto vertexBuffer = BufferCreate::CreateVertexBuffer(mesh.GetVertexData(), vertexBufferSize);
            mesh.SetVertexBuffer(vertexBuffer);

            // インデックスバッファの作成とセット
            auto indexBufferSize = UINT(sizeof(uint32_t) * mesh.GetIndices().size());
            auto indexBuffer = BufferCreate::CreateIndexBuffer(mesh.GetIndices(), indexBufferSize);
            mesh.SetIndexBuffer(indexBuffer);
        }
    }
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

        My3DLib::Material material{};
        material.g_ImageData = imageData;
        material.g_AlphaMode = m.alphaMode;

        m_Model.materials[""].push_back(material);
    }
}

void VRMModelLoader::MakeModelMaterial(My3DLib::Model& model)
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
