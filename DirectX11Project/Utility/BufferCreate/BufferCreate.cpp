#include "BufferCreate.h"
#include "../Mesh/Mesh.h"

ID3D11Buffer* BufferCreate::CreateVertexBuffer(UINT strides, std::vector<DirectX::XMFLOAT3> vertices)
{
	// 頂点バッファの作成
	// 頂点バッファとはシステムメモリ外、すなわちGPU側にあるメモリに頂点データを配置するためのもの
	D3D11_BUFFER_DESC bufferDesc{};
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.ByteWidth = strides * static_cast<UINT>(vertices.size());
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA subResourceData{};
	ZeroMemory(&subResourceData, sizeof(subResourceData));
	subResourceData.pSysMem = &vertices[0];

	ID3D11Buffer* buffer{ nullptr };
	if (FAILED(DirectX11App::g_Device->CreateBuffer(&bufferDesc, &subResourceData, &buffer))) {
		DebugLog::LogError("Vertex Buffer Create Failed.");
		return nullptr;
	}

	return buffer;
}

bool BufferCreate::SetVertexBuffer(std::map<std::string, std::vector<My3DLib::Mesh>>& meshMap) {

    UINT strides = sizeof(My3DLib::VertexData);
	for (auto& meshs : meshMap) {
		for (auto& mesh : meshs.second) {
			// 頂点バッファの作成
            mesh.SetVertexBuffer(CreateVertexBuffer(strides, mesh.GetVertices()));
		}
	}

	return true;
}

ID3D11Buffer* BufferCreate::CreateIndexBuffer(UINT strides, std::vector<UINT> indices)
{
    // インデックスバッファの作成
    // インデックスバッファとは、頂点重複分の無駄を省くためのもの
    D3D11_BUFFER_DESC bufferDesc{};
    ZeroMemory(&bufferDesc, sizeof(bufferDesc));
    bufferDesc.ByteWidth = strides * static_cast<UINT>(indices.size());
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

    D3D11_SUBRESOURCE_DATA subResourceData{};
    ZeroMemory(&subResourceData, sizeof(subResourceData));
    subResourceData.pSysMem = &indices[0];

    ID3D11Buffer* buffer{ nullptr };
    if (FAILED(DirectX11App::g_Device->CreateBuffer(&bufferDesc, &subResourceData, &buffer))) {
        DebugLog::LogError("Index Buffer Create Failed.");
        return nullptr;
    }
    
    return buffer;
}

bool BufferCreate::SetIndexBuffer(std::map<std::string, std::vector<My3DLib::Mesh>>& meshMap)
{
    UINT strides = sizeof(UINT);
    for (auto& meshs : meshMap) {
        for (auto& mesh : meshs.second) {
            // インデックスバッファーの設定
            mesh.SetIndexBuffer(CreateIndexBuffer(strides, mesh.GetIndices()));
        }
    }

    return true;
}
