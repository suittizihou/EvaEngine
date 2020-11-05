#include "BufferCreate.h"
#include "../Mesh/Mesh.h"

bool BufferCreate::SetVertexBuffer(std::map<std::string, std::vector<My3DLib::Mesh>>& meshMap) {

    UINT strides = sizeof(My3DLib::VertexData);
	for (auto& meshs : meshMap) {
		for (auto& mesh : meshs.second) {
			// 頂点バッファの作成
            // 頂点バッファとはシステムメモリ外、すなわちGPU側にあるメモリに頂点データを配置するためのもの
			D3D11_BUFFER_DESC bufferDesc{};
			ZeroMemory(&bufferDesc, sizeof(bufferDesc));
			bufferDesc.ByteWidth = strides * static_cast<UINT>(mesh.GetVertices().size());
			bufferDesc.Usage = D3D11_USAGE_DEFAULT;
			bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

			D3D11_SUBRESOURCE_DATA subResourceData{};
			ZeroMemory(&subResourceData, sizeof(subResourceData));
			subResourceData.pSysMem = &mesh.GetVertices()[0];

			ID3D11Buffer* buffer{ nullptr };
			if (FAILED(DirectX11App::g_Device->CreateBuffer(&bufferDesc, &subResourceData, &buffer))) {
				DebugLog::LogError("Vertex Buffer Create Failed.");
				return false;
			}
            mesh.SetVertexBuffer(buffer);
		}
	}

	return true;
}

bool BufferCreate::SetIndexBuffer(std::map<std::string, std::vector<My3DLib::Mesh>>& meshMap)
{
    for (auto& meshs : meshMap) {
        for (auto& mesh : meshs.second) {
            // インデックスバッファの作成
            // インデックスバッファとは、頂点重複分の無駄を省くためのもの
            D3D11_BUFFER_DESC bufferDesc{};
            ZeroMemory(&bufferDesc, sizeof(bufferDesc));
            bufferDesc.ByteWidth = (sizeof(UINT)) * static_cast<UINT>(mesh.GetIndices().size());
            bufferDesc.Usage = D3D11_USAGE_DEFAULT;
            bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
            //bufferDesc.CPUAccessFlags = 0;

            D3D11_SUBRESOURCE_DATA subResourceData{};
            ZeroMemory(&subResourceData, sizeof(subResourceData));
            subResourceData.pSysMem = &mesh.GetIndices()[0];

            ID3D11Buffer* buffer{ nullptr };
            if (FAILED(DirectX11App::g_Device->CreateBuffer(&bufferDesc, &subResourceData, &buffer))) {
                DebugLog::LogError("Index Buffer Create Failed.");
                return false;
            }
            // インデックスバッファーの設定
            mesh.SetIndexBuffer(buffer);
        }
    }

    return true;
}
