#include <stdexcept>
#include <string>
#include <fbxsdk.h>

#include "FBXModelLoader.h"

#include "../../../Mesh/Mesh.h"
#include "../../../Material/Material.h"

My3DLib::Model FBXModelLoader::LoadFbxFile(const char* fileName)
{
    // FbxManager作成
    FbxManager* fbx_manager = fbxsdk::FbxManager::Create();
    if (fbx_manager == nullptr)
    {
        std::runtime_error("FbxManagerの作成に失敗しました");
        return My3DLib::Model();
    }

    // FbxImporter作成
    FbxImporter* fbx_importer = FbxImporter::Create(fbx_manager, "");
    if (fbx_importer == nullptr) {
        fbx_manager->Destroy();
        std::runtime_error("FbxImporterの作成に失敗しました");
        return My3DLib::Model();
    }

    // FbxSceneを生成
    FbxScene* fbx_scene = FbxScene::Create(fbx_manager, "");
    if (fbx_scene == nullptr) {
        fbx_importer->Destroy();
        fbx_manager->Destroy();
        std::runtime_error("FbxSceneの作成に失敗しました");
        return My3DLib::Model();
    }

    //// IOSettingを生成
    //FbxIOSettings* ioSettings = FbxIOSettings::Create(manager, IOSROOT);
    //if (ioSettings == nullptr) {
    //    manager->Destroy();
    //    importer->Destroy();
    //    scene->Destroy();
    //    std::runtime_error("FbxIOSettingsの作成に失敗しました");
    //    return Model();
    //}
    //manager->SetIOSettings(ioSettings);

    // Fileを初期化
    fbx_importer->Initialize(fileName/*, -1, manager->GetIOSettings()*/);
    // sceneにインポート
    fbx_importer->Import(fbx_scene);

    // 三角ポリゴン化
    FbxGeometryConverter geometryConverter(fbx_manager);
    geometryConverter.Triangulate(fbx_scene, true);

    fbxsdk::FbxNode* root_node = fbx_scene->GetRootNode();
    // Scene解析
    std::map<std::string, FbxNode*> mesh_node_list;
    // メッシュNodeを探す
    FindMeshNode(root_node, mesh_node_list);

    for (auto data : mesh_node_list) {
        // mesh作成
        CreateMesh(data.first.c_str(), data.second->GetMesh());
    }

    // 関連するすべてのオブジェクトが解放される
    // インポータ―解放
    fbx_importer->Destroy();
    // シーン解放
    fbx_scene->Destroy();
    // マネージャ解放
    fbx_manager->Destroy();

    return m_Model;
}

void FBXModelLoader::FindMeshNode(fbxsdk::FbxNode* node, std::map<std::string, fbxsdk::FbxNode*>& list)
{
    if (node == nullptr) return;

    for (int i = 0; i < node->GetNodeAttributeCount(); i++) {
        fbxsdk::FbxNodeAttribute* attribute = node->GetNodeAttributeByIndex(i);

        // Attributeがメッシュなら追加
        if (attribute->GetAttributeType() == fbxsdk::FbxNodeAttribute::EType::eMesh) {
            list[node->GetName()] = node;
            break;
        }

        for (int i = 0; i < node->GetChildCount(); i++) {
            FindMeshNode(node->GetChild(i), list);
        }
    }
}

bool FBXModelLoader::CreateMesh(const char* node_name, fbxsdk::FbxMesh* mesh)
{
    // 頂点バッファの取得
    fbxsdk::FbxVector4* vertices = mesh->GetControlPoints();
    // インデックスバッファの取得
    int* indices = mesh->GetPolygonVertices();
    // 頂点座標の数の取得
    int polygon_vertex_count = mesh->GetPolygonVertexCount();

    std::vector<DirectX::XMFLOAT3> vertexs;
    // GetPolygonVertexCount => 頂点数
    for (int i = 0; i < polygon_vertex_count; i++) {
        // インデックスバッファから頂点番号を取得
        int index = indices[i];
        DirectX::XMFLOAT3 vertex{};
        // 頂点座標リストから座標を取得する
        vertex.x = (float)-vertices[index][0];
        vertex.y = (float)vertices[index][1];
        vertex.z = (float)vertices[index][2];

        // 追加
        vertexs.push_back(vertex);
    }
    // 頂点情報のセット
    m_Model.meshes[node_name][0].SetVertices(vertexs);

    fbxsdk::FbxArray<fbxsdk::FbxVector4> normals;
    // 法線リストの取得
    mesh->GetPolygonVertexNormals(normals);

    // 法線設定
    for (int i = 0; i < normals.Size(); i++) {
        m_Model.meshes[node_name][0].SetNormal(i, DirectX::XMFLOAT3((float)normals[i][0], (float)normals[i][1], (float)normals[i][0]));
    }

    // ポリゴン数の取得
    int polygon_count = mesh->GetPolygonCount();

    std::vector<unsigned int> tempIndices;
    // ポリゴンの数だけ連番として保存する
    for (int i = 0; i < polygon_count; i++) {
        tempIndices.push_back(i * 3 + 2);
        tempIndices.push_back(i * 3 + 1);
        tempIndices.push_back(i * 3);
    }

    // 頂点を使用する順番を保持
    m_Model.meshes[node_name][0].SetIndices(tempIndices);

    return true;
}
