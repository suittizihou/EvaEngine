#include "BufferCreate.h"

ID3D11Buffer* BufferCreate::CreateVertexBuffer(ModelData::VertexData* vertexData, UINT vertexNum) {
	// 頂点バッファの作成
	D3D11_BUFFER_DESC bufferDesc{};
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.ByteWidth = sizeof(ModelData::VertexData) * vertexNum;
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA subResourceData{};
	ZeroMemory(&subResourceData, sizeof(subResourceData));
	subResourceData.pSysMem = vertexData;

	ID3D11Buffer* buffer{ nullptr };
	if (FAILED(DirectX11App::g_Device->CreateBuffer(&bufferDesc, &subResourceData, &buffer))) {
		DebugLog::LogError("Vertex Buffer Create Failed.");
		return nullptr;
	}

	return buffer;
}
ID3D11Buffer* BufferCreate::CreateIndexBuffer(UINT* index, UINT indexNum)
{
    // インデックスバッファの作成
    D3D11_BUFFER_DESC bufferDesc{};
    ZeroMemory(&bufferDesc, sizeof(bufferDesc));
    bufferDesc.ByteWidth = (sizeof(UINT)) * indexNum;
    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bufferDesc.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA subResourceData{};
    ZeroMemory(&subResourceData, sizeof(subResourceData));
    subResourceData.pSysMem = index;

    ID3D11Buffer* buffer{ nullptr };
    if (FAILED(DirectX11App::g_Device->CreateBuffer(&bufferDesc, &subResourceData, &buffer))) {
        DebugLog::LogError("Index Buffer Create Failed.");
        return nullptr;
    }

    return buffer;
}
