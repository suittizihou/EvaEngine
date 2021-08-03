#include <stdexcept>
#include <string>
#include <fbxsdk.h>

#include "FBXModelLoader.h"

#include "../../../../System/DebugLog/DebugLog.h"
#include "../../../Mesh/Mesh.h"
#include "../../../Material/Material.h"

using namespace EvaEngine;
using namespace EvaEngine::Internal;

ModelData FBXModelLoader::LoadModel(const char* fileName)
{
    // FbxManager�쐬
    fbxsdk::FbxManager* fbx_manager = fbxsdk::FbxManager::Create();
    if (fbx_manager == nullptr)
    {
        DebugLog::LogError(u8"FbxManager�̍쐬�Ɏ��s���܂���");
        return ModelData();
    }

    // FbxImporter�쐬
    FbxImporter* fbx_importer = FbxImporter::Create(fbx_manager, "");
    if (fbx_importer == nullptr) {
        fbx_manager->Destroy();
        DebugLog::LogError(u8"FbxImporter�̍쐬�Ɏ��s���܂���");
        return ModelData();
    }

    // FbxScene�𐶐�
    fbxsdk::FbxScene* fbx_scene = fbxsdk::FbxScene::Create(fbx_manager, "");
    if (fbx_scene == nullptr) {
        fbx_importer->Destroy();
        fbx_manager->Destroy();
        DebugLog::LogError(u8"FbxScene�̍쐬�Ɏ��s���܂���");
        return ModelData();
    }

    // File��������
    fbx_importer->Initialize(fileName);
    // scene�ɃC���|�[�g
    fbx_importer->Import(fbx_scene);

    FbxGeometryConverter converter(fbx_manager);
    // �|���S�����O�p�`�ɂ���
    converter.Triangulate(fbx_scene, true);

    int materialNum = fbx_scene->GetSrcObjectCount<FbxSurfaceMaterial>();
    for (int i = 0; i < materialNum; ++i) {
        LoadMaterial(fbx_scene->GetSrcObject<FbxSurfaceMaterial>(i));
    }

    std::map<std::string, FbxNode*> mesh_node_list;
    // ���b�V��Node��T��
    FindMeshNode(fbx_scene->GetRootNode(), mesh_node_list);

    for (auto data : mesh_node_list) {
        // mesh�쐬
        CreateMesh(data.first.c_str(), data.second->GetMesh());
    }

    // �֘A���邷�ׂẴI�u�W�F�N�g����������
    // �C���|�[�^�\���
    fbx_importer->Destroy();
    // �V�[�����
    fbx_scene->Destroy();
    // �}�l�[�W�����
    fbx_manager->Destroy();

    return m_Model;
}

void FBXModelLoader::LoadMaterial(fbxsdk::FbxSurfaceMaterial* material)
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

    m_Model.materials[material->GetName()] = tempMaterial;

    // �e�N�X�`���ǂݍ���
    // Diffuse�v���p�e�B���擾
    prop = material->FindProperty(FbxSurfaceMaterial::sDiffuse);
    FbxFileTexture* texture = nullptr;
    std::string keyword;
    int textureNum = prop.GetSrcObjectCount<FbxFileTexture>();
    if (textureNum > 0) {
        // prop����FbxFileTexture���擾
        texture = prop.GetSrcObject<FbxFileTexture>(0);
    }
    else {
        // FbxLaveredTexture����FbxFileTexture���擾
        int layerNum = prop.GetSrcObjectCount<FbxLayeredTexture>();
        if (layerNum > 0) {
            texture = prop.GetSrcObject<FbxFileTexture>(0);
        }
    }

    if (texture != nullptr &&
        LoadTexture(texture, keyword)) {
        // �ǂݍ��񂾃e�N�X�`���ƃ}�e���A���̊֌W��ێ�

    }
}

bool FBXModelLoader::LoadTexture(fbxsdk::FbxFileTexture* texture, std::string& keyword)
{
    return false;
}

void FBXModelLoader::FindMeshNode(fbxsdk::FbxNode* node, std::map<std::string, fbxsdk::FbxNode*>& list)
{
    for (int i = 0; i < node->GetNodeAttributeCount(); i++)
    {
        FbxNodeAttribute* attribute = node->GetNodeAttributeByIndex(i);

        // Attribute�����b�V���Ȃ�ǉ�
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

bool FBXModelLoader::CreateMesh(const char* node_name, fbxsdk::FbxMesh* mesh)
{
    // ���_�o�b�t�@�̎擾
    fbxsdk::FbxVector4* vertices = mesh->GetControlPoints();
    // �C���f�b�N�X�o�b�t�@�̎擾
    int* indices = mesh->GetPolygonVertices();
    // ���_���W�̐��̎擾
    int polygon_vertex_count = mesh->GetPolygonVertexCount();
    
    std::vector<VertexData> vertexData{};

    // GetPolygonVertexCount => ���_��
    for (int i = 0; i < polygon_vertex_count; ++i) {
        // �C���f�b�N�X�o�b�t�@���璸�_�ԍ����擾
        int index = indices[i];
        VertexData vertex{};
        vertex.position.x = (float)-vertices[index][0];
        vertex.position.y = (float)vertices[index][1];
        vertex.position.z = (float)vertices[index][2];

        // ���_���W���X�g������W���擾����
        vertexData.push_back(vertex);
    }

    for (int i = 0; i < vertexData.size(); ++i) {
        vertexData[i].color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
    }

    fbxsdk::FbxArray<fbxsdk::FbxVector4> normals;
    // �@�����X�g�̎擾
    mesh->GetPolygonVertexNormals(normals);

    // �@���ݒ�
    for (int i = 0; i < normals.Size(); ++i) {
        // ���_�@�����X�g����@�����擾����
        vertexData[i].normal = DirectX::XMFLOAT3((float)-normals[i][0], (float)normals[i][1], (float)normals[i][2]);
    }

    // �|���S�����̎擾
    int polygon_count = mesh->GetPolygonCount();

    std::vector<unsigned int> tempIndices;
    // �|���S���̐������A�ԂƂ��ĕۑ�����
    for (int i = 0; i < polygon_count; ++i) {
        tempIndices.push_back(i * 3 + 2);
        tempIndices.push_back(i * 3 + 1);
        tempIndices.push_back(i * 3);
    }

    Mesh tempMesh{};
    tempMesh.SetVertexData(vertexData);
    // �C���f�b�N�X�o�b�t�@���Z�b�g
    tempMesh.SetIndices(tempIndices);
    // ���O���Z�b�g
    tempMesh.name = node_name;

    // ���_���̃Z�b�g
    m_Model.meshes[node_name].push_back(tempMesh);

    mesh->Destroy();

    return true;
}
