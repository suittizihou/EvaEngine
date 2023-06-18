#include "OBJModelLoader.h"
#include "../../../../System/DebugLog/DebugLog.h"
#include "../../../StringAssist/StringAssist.h"

using namespace EvaEngine;
using namespace EvaEngine::Internal;

void Replase(char searchChar, char replaceChar, char* buffer) {
    int len = static_cast<int>(strlen(buffer));

    for (int i = 0; i < len; ++i) {
        if (buffer[i] != searchChar) continue;

        buffer[i] = replaceChar;
    }
}

void OBJModelLoader::LoadModel(const char* fileName, std::shared_ptr<EvaEngine::ModelData>& model)
{
    if (!CreateMesh(model, fileName)) {
        DebugLog::LogError("�t�@�C���� : " + std::string{ fileName } + " ���f���̓ǂݍ��݂Ɏ��s���܂����B");
        return;
    }
}

bool OBJModelLoader::CreateMesh(std::shared_ptr<EvaEngine::ModelData>& model, const char* fileName)
{
    FILE* file{ nullptr };
    fopen_s(&file, fileName, "r");

    if (file == nullptr) return false;

    std::vector<VertexData> vertexData{};
    std::vector<unsigned int> indices{};
    std::vector<DirectX::XMFLOAT3> vertices;
    std::vector<DirectX::XMFLOAT3> normals;

    const int LineBufferLength = 1024;
    char buffer[LineBufferLength];

    while (fgets(buffer, LineBufferLength, file) != nullptr) {
        // �R�����g�͖���
        if (buffer[0] == '#') continue;

        char* parsePoint = strchr(buffer, ' ');
        if (parsePoint == nullptr) continue;

        Replase('\n', '\0', buffer);

        // ���_�֘A
        if (buffer[0] == 'v') {
            // ���_���W
            if (buffer[1] == ' ') {
                ParseVKeywordTag(vertices, &parsePoint[1]);
                // X���𔽓]������
                vertices[vertices.size() - 1].x *= -1.0f;
            }
            // �@�����W
            else if (buffer[1] == 'n') {
                ParseVKeywordTag(normals, &parsePoint[1]);
                // X���𔽓]������
                normals[normals.size() - 1].x *= -1.0f;
            }
        }
        // �ʏ��
        else if (buffer[0] == 'f') {
            ParseFKeywordTag(_Out_ vertexData, _Out_ indices, vertices, normals, &parsePoint[1]);
        }
    }

    Mesh mesh{};
    mesh.SetVertexData(vertexData);
    mesh.SetIndices(indices);
    model->meshes["default"].push_back(mesh);

    return true;
}

void OBJModelLoader::ParseVKeywordTag(std::vector<DirectX::XMFLOAT3>& data, char* buffer)
{
    std::vector<std::string> splitStrings;
    StringAssist::Split(' ', buffer, splitStrings);

    int count{};
    float values[3] = { 0.0f };

    for (std::string str : splitStrings) {
        values[count] = static_cast<float>(atof(str.c_str()));
        count += 1;
    }

    data.push_back(DirectX::XMFLOAT3(values[0], values[1], values[2]));
}

void OBJModelLoader::ParseFKeywordTag(
    _Out_ std::vector<VertexData>& outVertexData,
    _Out_ std::vector<unsigned int>& outIndices,
    std::vector<DirectX::XMFLOAT3>& vertices,
    std::vector<DirectX::XMFLOAT3>& normals, 
    char* buffer)
{
    int count{};
    int vertexInfo[3] = {
        -1, -1, -1
    };
    std::vector<std::string> spaceSplit;
    StringAssist::Split(' ', buffer, spaceSplit);

    for (int i = 0; i < spaceSplit.size(); ++i) {
        VertexData vertexData{};
        ParseShashKeywordTag(vertexInfo, (char*)spaceSplit[i].c_str());

        for (int i = 0; i < 3; ++i) {
            if (vertexInfo[i] == -1) continue;

            int id = vertexInfo[i];

            switch (i) {
            case 0:
                vertexData.position = vertices[id];
                break;

            case 2:
                vertexData.normal = normals[id];
                break;
            }
        }

        // ���_�o�b�t�@���X�g�ɒǉ�
        outVertexData.push_back(vertexData);

        // �C���f�b�N�X�o�b�t�@�ɒǉ�
        outIndices.push_back(static_cast<unsigned int>(outVertexData.size() - 1));
    }

    // �|���S���쐬�̒��_���Ԃ𔽓]����
    unsigned int size = static_cast<unsigned int>(outIndices.size());
    unsigned int temp = outIndices[size - 1];
    outIndices[size - 1] = outIndices[size - 3];
    outIndices[size - 3] = temp;
}

void OBJModelLoader::ParseShashKeywordTag(int* list, char* buffer)
{
    int counter{};
    std::vector<std::string> slashSplit;
    StringAssist::Split('/', buffer, slashSplit);

    for (std::string str : slashSplit) {
        if (str.size() > 0) {
            list[counter] = atoi(str.c_str()) - 1;
        }
        counter += 1;
    }
}