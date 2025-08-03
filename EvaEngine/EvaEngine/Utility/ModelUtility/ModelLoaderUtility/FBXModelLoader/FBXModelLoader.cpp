#include <stdexcept>
#include <string>
#include <fbxsdk.h>

#include "FBXModelLoader.h"

#include "../../../../System/DebugLog/DebugLog.h"
#include "../../../Mesh/Mesh.h"
#include "../../../Material/Material.h"

using namespace EvaEngine;
using namespace EvaEngine::Internal;

void FBXModelLoader::LoadModel(const std::u8string& fileName, std::shared_ptr<EvaEngine::ModelData>& model)
{
    // FbxManager作成
    fbxsdk::FbxManager* fbx_manager = fbxsdk::FbxManager::Create();
    if (fbx_manager == nullptr)
    {
        DebugLog::LogError(u8"FbxManagerの作成に失敗しました");
        return;
    }

    // FbxImporter作成
    fbxsdk::FbxImporter* fbx_importer = fbxsdk::FbxImporter::Create(fbx_manager, "");
    if (fbx_importer == nullptr) {
        
        fbx_manager->Destroy();
        DebugLog::LogError(u8"FbxImporterの作成に失敗しました");
        return;
    }

    // FbxScene作成
    fbxsdk::FbxScene* fbx_scene = fbxsdk::FbxScene::Create(fbx_manager, "");
    if (fbx_scene == nullptr) {
        fbx_importer->Destroy();
        fbx_manager->Destroy();
        DebugLog::LogError(u8"FbxSceneの作成に失敗しました");
        return;
    }

    // Fileを初期化
    fbx_importer->Initialize(reinterpret_cast<const char*>(fileName.c_str()));
    // sceneにインポート
    fbx_importer->Import(fbx_scene);

    FbxGeometryConverter converter(fbx_manager);

    // ポリゴンを三角形にする
    converter.Triangulate(fbx_scene, true);

    int materialNum = fbx_scene->GetSrcObjectCount<FbxSurfaceMaterial>();
    for (int i = 0; i < materialNum; ++i) {
        LoadMaterial(model, fbx_scene->GetSrcObject<FbxSurfaceMaterial>(i));
    }


    std::map<std::string, FbxNode*> mesh_node_list;
    // メッシュNodeを探す
    FindMeshNode(fbx_scene->GetRootNode(), mesh_node_list);

    for (auto data : mesh_node_list) {
        // mesh作成
        CreateMesh(model, data.first.c_str(), data.second->GetMesh());
    }

    // 関連する全てのオブジェクトが解放される
    // インポータ―解放
    fbx_importer->Destroy();
    // シーン解放
    fbx_scene->Destroy();
    // マネージャ解放
    fbx_manager->Destroy();
}

void FBXModelLoader::LoadMaterial(std::shared_ptr<EvaEngine::ModelData>& model, fbxsdk::FbxSurfaceMaterial* material)
{
    Material tempMaterial{};

    enum class MaterialOrder {
        Ambient,
        Diffuse,
        Specular,
        MaxOrder
    };

    FbxDouble3 colors[(int)MaterialOrder::MaxOrder];
    FbxDouble factors[(int)MaterialOrder::MaxOrder];
    FbxProperty prop = material->FindProperty(FbxSurfaceMaterial::sAmbient);
    if (material->GetClassId().Is(FbxSurfaceLambert::ClassId)) {
        const char* elementCheckList[] = {
            FbxSurfaceMaterial::sAmbient,
            FbxSurfaceMaterial::sDiffuse
        };

        const char* factorCheckList[] = {
            FbxSurfaceMaterial::sAmbientFactor,
            FbxSurfaceMaterial::sDiffuseFactor
        };

        for (int i = 0; i < 2; ++i) {
            prop = material->FindProperty(elementCheckList[i]);
            if (prop.IsValid()) {
                colors[i] = prop.Get<FbxDouble3>();
            }
            else {
                colors[i] = FbxDouble3(1.0f, 1.0f, 1.0f);
            }

            prop = material->FindProperty(factorCheckList[i]);
            if (prop.IsValid()) {
                factors[i] = prop.Get<FbxDouble>();
            }
            else {
                factors[i] = 1.0f;
            }
        }
    }

    FbxDouble3 color = colors[(int)MaterialOrder::Ambient];
    FbxDouble factor = factors[(int)MaterialOrder::Ambient];
    tempMaterial.ambient = DirectX::XMFLOAT4((float)color[0], (float)color[1], (float)color[2], (float)factor);

    color = colors[(int)MaterialOrder::Diffuse];
    factor = factors[(int)MaterialOrder::Diffuse];
    tempMaterial.diffuse = DirectX::XMFLOAT4((float)color[0], (float)color[1], (float)color[2], (float)factor);

    model->materials[material->GetName()] = tempMaterial;

    // テクスチャ読み込み
    // Diffuseプロパティを取得
    prop = material->FindProperty(FbxSurfaceMaterial::sDiffuse);
    FbxFileTexture* texture = nullptr;
    std::string keyword;
    int textureNum = prop.GetSrcObjectCount<FbxFileTexture>();
    if (textureNum > 0) {
        // propからFbxFileTextureを取得
        texture = prop.GetSrcObject<FbxFileTexture>(0);
    }
    else {
        // FbxLaveredTextureからFbxFileTextureを取得
        int layerNum = prop.GetSrcObjectCount<FbxLayeredTexture>();
        if (layerNum > 0) {
            texture = prop.GetSrcObject<FbxFileTexture>(0);
        }
    }

    if (texture != nullptr &&
        LoadTexture(model, texture, keyword)) {
        // 読み込んだテクスチャとマテリアルの関係を保持

    }
}

bool FBXModelLoader::LoadTexture(std::shared_ptr<EvaEngine::ModelData>& model, fbxsdk::FbxFileTexture* texture, std::string& keyword)
{
    return false;
}

void FBXModelLoader::FindMeshNode(fbxsdk::FbxNode* node, std::map<std::string, fbxsdk::FbxNode*>& list)
{
    for (int i = 0; i < node->GetNodeAttributeCount(); i++)
    {
        FbxNodeAttribute* attribute = node->GetNodeAttributeByIndex(i);

        // Attributeがメッシュなら追加
        if (attribute->GetAttributeType() == FbxNodeAttribute::EType::eMesh)
        {
            list[node->GetName()] = node;
            break;
        }
    }

    for (int i = 0; i < node->GetChildCount(); i++)
    {
        FindMeshNode(node->GetChild(i), list);
    }
}

bool FBXModelLoader::CreateMesh(std::shared_ptr<EvaEngine::ModelData>& model, const char* node_name, fbxsdk::FbxMesh* mesh)
{
    // 頂点バッファの取得
    fbxsdk::FbxVector4* vertices = mesh->GetControlPoints();
    // インデックスバッファの取得
    int* indices = mesh->GetPolygonVertices();
    // 頂点座標の数の取得
    int polygon_vertex_count = mesh->GetPolygonVertexCount();
    
    std::vector<VertexData> vertexData(polygon_vertex_count);

    // GetPolygonVertexCount => 頂点数
    for (int i = 0; i < polygon_vertex_count; ++i) {
        // インデックスバッファから頂点番号を取得
        int index = indices[i];
        VertexData vertex{};
        vertex.position.x = (float)-vertices[index][0];
        vertex.position.y = (float)vertices[index][1];
        vertex.position.z = (float)vertices[index][2];

        // 頂点座標リストから座標を取得する
        vertexData[i] = vertex;
    }

    for (int i = 0; i < vertexData.size(); ++i) {
        vertexData[i].color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    }

    fbxsdk::FbxArray<fbxsdk::FbxVector4> normals;
    // 法線リストの取得
    mesh->GetPolygonVertexNormals(normals);

    // 法線設定
    for (int i = 0; i < normals.Size(); ++i) {
        // 頂点法線リストから法線を取得する
        vertexData[i].normal = DirectX::XMFLOAT3((float)-normals[i][0], (float)normals[i][1], (float)normals[i][2]);
    }

    // ポリゴン数の取得
    int polygon_count = mesh->GetPolygonCount();

    std::vector<unsigned int> tempIndices(polygon_count * 3);
    int polygonIndexNum = 0;
    // ポリゴンの数だけ連番として保存する
    for (int i = 0; i < polygon_count; ++i) {
        tempIndices[polygonIndexNum] = i * 3 + 2;
        polygonIndexNum++;

        tempIndices[polygonIndexNum] = i * 3 + 1;
        polygonIndexNum++;
        
        tempIndices[polygonIndexNum] = i * 3;
        polygonIndexNum++;
    }

    Mesh tempMesh{};
    tempMesh.SetVertexData(vertexData);
    // インデックスバッファをセット
    tempMesh.SetIndices(tempIndices);
    // 名前をセット
    tempMesh.name = node_name;

    // 頂点情報のセット
    model->meshes[node_name].push_back(tempMesh);

    mesh->Destroy();

    return true;
}
