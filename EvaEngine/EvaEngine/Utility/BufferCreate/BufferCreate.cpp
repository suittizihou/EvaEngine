#include "BufferCreate.h"
#include "../Mesh/Mesh.h"
#include "../ModelUtility/ModelData/ConstantBufferData.h"

using namespace EvaEngine::Internal;

ID3D11Buffer* BufferCreate::CreateVertexBuffer(const std::vector<VertexData>& vertices, size_t strides)
{
	// 頂点バッファの作成
	// 頂点バッファとはシステムメモリ外、すなわちGPU側にあるメモリに頂点データを配置するためのもの
	D3D11_BUFFER_DESC bufferDesc{};
	ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	bufferDesc.ByteWidth = static_cast<UINT>(strides * vertices.size());
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

bool BufferCreate::SetVertexBuffer(std::map<std::string, std::vector<Mesh>>& meshMap) {

    size_t strides = sizeof(VertexData);
	for (auto& meshs : meshMap) {
		for (auto& mesh : meshs.second) {
			// 頂点バッファの作成
            mesh.SetVertexBuffer(CreateVertexBuffer(mesh.GetVertexData(), strides));
		}
	}

	return true;
}

ID3D11Buffer* BufferCreate::CreateIndexBuffer(const std::vector<UINT>& indices, size_t strides)
{
    // インデックスバッファの作成
    // インデックスバッファとは、頂点重複分の無駄を省くためのもの
    D3D11_BUFFER_DESC bufferDesc{};
    ZeroMemory(&bufferDesc, sizeof(bufferDesc));
    bufferDesc.ByteWidth = static_cast<UINT>(strides * indices.size());
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

bool BufferCreate::SetIndexBuffer(std::map<std::string, std::vector<Mesh>>& meshMap)
{
    UINT strides = sizeof(UINT);
    for (auto& meshs : meshMap) {
        for (auto& mesh : meshs.second) {
            // インデックスバッファーの設定
            mesh.SetIndexBuffer(CreateIndexBuffer(mesh.GetIndices(), strides));
        }
    }

    return true;
}

ID3D11Buffer* BufferCreate::CreateConstantBuffer()
{
    D3D11_BUFFER_DESC bufferDesc{};
    ZeroMemory(&bufferDesc, sizeof(bufferDesc));
    bufferDesc.ByteWidth = ((sizeof(ConstantBufferData) + 256) & 0xFFFFFF00);
    bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

    ID3D11Buffer* buffer{ nullptr };
    if (FAILED(DirectX11App::g_Device->CreateBuffer(&bufferDesc, nullptr, &buffer))) {
        DebugLog::ShowErrorMessageWindow("Constant Buffer Create Failed.");
        return nullptr;
    }

    return buffer;
}
