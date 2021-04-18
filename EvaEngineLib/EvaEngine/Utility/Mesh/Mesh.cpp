#include "Mesh.h"
#include "../BufferCreate/BufferCreate.h"
#include <cmath>

using namespace EvaEngine;

Mesh::Mesh(int vertexSize)
{
	m_Vertexs.resize(vertexSize);
}

void Mesh::SetVertexNum(int vertexSize)
{
	m_Vertexs.resize(vertexSize);
}

void Mesh::SetVertexData(std::vector<VertexData> vertexDatas, bool isCreateIndices) {
	
	m_Vertexs = vertexDatas;

	// 頂点バッファを作成してセット
	m_VertexBuffer.Attach(BufferCreate::CreateVertexBuffer(m_Vertexs, sizeof(VertexData)));
	
	// インデックスバッファの作成をするならする
	if (isCreateIndices) {
		m_Indices = CreateIndices(m_Vertexs);
		m_IndexBuffer.Attach(BufferCreate::CreateIndexBuffer(m_Indices, sizeof(UINT)));
	}
}

void Mesh::SetVertexPos(int vertexNum, float x, float y, float z)
{
	m_Vertexs[vertexNum].position = DirectX::XMFLOAT3(x, y, z);
}

void Mesh::SetVertexNormal(int vertexNum, float x, float y, float z)
{
	m_Vertexs[vertexNum].normal = DirectX::XMFLOAT3(x, y, z);
}

void Mesh::SetVertexColor(int vertexNum, float r, float g, float b, float a)
{
	m_Vertexs[vertexNum].color = DirectX::XMFLOAT4(r, g, b, a);
}

void Mesh::SetVertexUV(int vertexNum, float u, float v)
{
	m_Vertexs[vertexNum].uv = DirectX::XMFLOAT2(u, v);
}

void Mesh::SetVertexBuffer(ID3D11Buffer* vertexBuffer)
{
	m_VertexBuffer.Attach(vertexBuffer);
}

std::vector<UINT> Mesh::CreateIndices(const std::vector<VertexData>& vertexDatas)
{
	std::vector<UINT> indices;
	int polyCount = static_cast<int>(std::ceil(static_cast<float>(vertexDatas.size()) / 3.0f));
	// ポリゴンの数だけ連番で保存
	for (int i = 0; i < polyCount; i++) {
		indices.push_back(i * 3 + 2);
		indices.push_back(i * 3 + 1);
		indices.push_back(i * 3);
	}

	return indices;
}

void Mesh::SetIndices(std::vector<unsigned int> indices)
{
	m_Indices = indices;
	m_IndexBuffer.Attach(BufferCreate::CreateIndexBuffer(m_Indices, sizeof(UINT)));
}

void Mesh::SetIndexBuffer(ID3D11Buffer* indexBuffer)
{
	m_IndexBuffer.Attach(indexBuffer);
}

void Mesh::SetMaterialName(UINT materialID)
{
	m_MaterialName = std::to_string(materialID);
}

void Mesh::SetMaterialName(std::string materialName)
{
	m_MaterialName = materialName;
}

std::vector<VertexData> Mesh::GetVertexData()
{
	return m_Vertexs;
}

ID3D11Buffer* const* Mesh::GetVertexBuffer()
{
	return m_VertexBuffer.GetAddressOf();
}

std::vector<unsigned int> Mesh::GetIndices()
{
	return m_Indices;
}

ID3D11Buffer* Mesh::GetIndexBuffer()
{
	return m_IndexBuffer.Get();
}

std::string Mesh::GetMaterialName() const
{
	return m_MaterialName;
}