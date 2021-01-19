#include "OBJModelLoader.h"
#include "../../../../System/DebugLog/DebugLog.h"

void Split(char split_char, char* buffer, std::vector<std::string>& out)
{
    int count = 0;
    if (buffer == nullptr)
    {
        return;
    }

    int start_point = 0;

    while (buffer[count] != '\0')
    {
        if (buffer[count] == split_char)
        {
            if (start_point != count)
            {
                char split_str[256] = { 0 };
                strncpy_s(split_str, 256, &buffer[start_point], count - start_point);
                out.emplace_back(split_str);
            }
            else
            {
                out.emplace_back("");
            }
            start_point = count + 1;
        }
        count += 1;
    }

    if (start_point != count)
    {
        char split_str[256] = { 0 };
        strncpy_s(split_str, 256, &buffer[start_point], count - start_point);
        out.emplace_back(split_str);
    }
}

void Replase(char searchChar, char replaceChar, char* buffer) {
    int len = static_cast<int>(strlen(buffer));

    for (int i = 0; i < len; ++i) {
        if (buffer[i] != searchChar) continue;

        buffer[i] = replaceChar;
    }
}

My3DLib::ModelData OBJModelLoader::LoadModel(const char* fileName)
{
    My3DLib::ModelData modelData{};
    if (!CreateMesh(modelData, fileName)) {
        DebugLog::LogError("ファイル名 : " + std::string{ fileName } + " モデルの読み込みに失敗しました。");
        return modelData;
    }

    return modelData;
}

bool OBJModelLoader::CreateMesh(My3DLib::ModelData& model, const char* fileName)
{
    FILE* file{ nullptr };
    fopen_s(&file, fileName, "r");

    if (file == nullptr) return false;

    std::vector<My3DLib::VertexData> vertexData{};
    std::vector<unsigned int> indices{};
    std::vector<DirectX::XMFLOAT3> vertices;
    std::vector<DirectX::XMFLOAT3> normals;

    const int LineBufferLength = 1024;
    char buffer[LineBufferLength];

    while (fgets(buffer, LineBufferLength, file) != nullptr) {
        // コメントは無視
        if (buffer[0] == '#') continue;

        char* parsePoint = strchr(buffer, ' ');
        if (parsePoint == nullptr) continue;

        Replase('\n', '\0', buffer);

        // 頂点関連
        if (buffer[0] == 'v') {
            // 頂点座標
            if (buffer[1] == ' ') {
                ParseVKeywordTag(vertices, &parsePoint[1]);
                // X軸を反転させる
                vertices[vertices.size() - 1].x *= -1.0f;
            }
            // 法線座標
            else if (buffer[1] == 'n') {
                ParseVKeywordTag(normals, &parsePoint[1]);
                // X軸を反転させる
                normals[normals.size() - 1].x *= -1.0f;
            }
        }
        // 面情報
        else if (buffer[0] == 'f') {
            ParseFKeywordTag(_Out_ vertexData, _Out_ indices, vertices, normals, &parsePoint[1]);
        }
    }

    My3DLib::Mesh mesh{};
    mesh.SetVertexData(vertexData);
    mesh.SetIndices(indices);
    model.meshes["default"].push_back(mesh);

    return true;
}

void OBJModelLoader::ParseVKeywordTag(std::vector<DirectX::XMFLOAT3>& data, char* buffer)
{
    std::vector<std::string> splitStrings;
    Split(' ', buffer, splitStrings);

    int count{};
    float values[3] = { 0.0f };

    for (std::string str : splitStrings) {
        values[count] = static_cast<float>(atof(str.c_str()));
        count += 1;
    }

    data.push_back(DirectX::XMFLOAT3(values[0], values[1], values[2]));
}

void OBJModelLoader::ParseFKeywordTag(
    _Out_ std::vector<My3DLib::VertexData>& outVertexData,
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
    Split(' ', buffer, spaceSplit);

    for (int i = 0; i < spaceSplit.size(); ++i) {
        My3DLib::VertexData vertexData{};
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

        // 頂点バッファリストに追加
        outVertexData.push_back(vertexData);

        // インデックスバッファに追加
        outIndices.push_back(static_cast<unsigned int>(outVertexData.size() - 1));
    }

    // ポリゴン作成の頂点順番を反転する
    unsigned int size = static_cast<unsigned int>(outIndices.size());
    unsigned int temp = outIndices[size - 1];
    outIndices[size - 1] = outIndices[size - 3];
    outIndices[size - 3] = temp;
}

void OBJModelLoader::ParseShashKeywordTag(int* list, char* buffer)
{
    int counter{};
    std::vector<std::string> slashSplit;
    Split('/', buffer, slashSplit);

    for (std::string str : slashSplit) {
        if (str.size() > 0) {
            list[counter] = atoi(str.c_str()) - 1;
        }
        counter += 1;
    }
}