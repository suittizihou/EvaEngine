#include "Mesh.h"

using namespace My3DLib;

std::vector<DirectX::XMFLOAT3> Mesh::GetVertices()
{
	return m_Vertices;
}

ID3D11Buffer* const* My3DLib::Mesh::GetVertexBuffer()
{
	return m_VertexBuffer.GetAddressOf();
}

std::vector<unsigned int> Mesh::GetIndices()
{
	return m_Indices;
}

ID3D11Buffer* My3DLib::Mesh::GetIndexBuffer()
{
	return m_IndexBuffer.Get();
}

std::vector<DirectX::XMFLOAT3> Mesh::GetNormal()
{
	return m_Normals;
}

std::vector<DirectX::XMFLOAT2> Mesh::GetUV()
{
	return m_UVs;
}

int My3DLib::Mesh::GetMaterialID()
{
	return m_MaterialID;
}

void Mesh::SetVertices(std::vector<DirectX::XMFLOAT3> vertices, bool isCreateIndices)
{
	m_Vertices = vertices;

	// インデックスバッファの作成をするならする
	if (isCreateIndices) CreateIndices();

	// 法線情報の数を頂点数と同じにする
	m_Normals.resize(vertices.size());
	// 頂点カラー情報の数を頂点数と同じにする
	m_Color.resize(vertices.size());
	// UV座標の数を頂点数と同じにする
	m_UVs.resize(vertices.size());
}

void Mesh::SetVertices(std::vector<My3DLib::VertexData> vertices, bool isCreateIndices) {
	for (const auto& vertex : vertices) {
		m_Vertices.push_back(vertex.position);
		m_Normals.push_back(vertex.normal);
		m_Color.push_back(vertex.color);
		m_UVs.push_back(vertex.uv);
	}

	// インデックスバッファの作成をするならする
	if (isCreateIndices) CreateIndices();
}

void My3DLib::Mesh::SetVertexBuffer(ID3D11Buffer* vertexBuffer)
{
	m_VertexBuffer.Attach(vertexBuffer);
}

void My3DLib::Mesh::CreateIndices()
{
	int polyCount = static_cast<UINT>(m_Vertices.size()) / 3;
	// ポリゴンの数だけ連番で保存
	for (int i = 0; i < polyCount; i++) {
		m_Indices.push_back(i * 3 + 2);
		m_Indices.push_back(i * 3 + 1);
		m_Indices.push_back(i * 3);
	}
}

void Mesh::SetIndices(std::vector<unsigned int> indices)
{
	m_Indices = indices;
}

void My3DLib::Mesh::SetIndexBuffer(ID3D11Buffer* indexBuffer)
{
	m_IndexBuffer.Attach(indexBuffer);
}

void Mesh::SetNormals(std::vector<DirectX::XMFLOAT3> normals)
{
	m_Normals = normals;
}

void Mesh::SetNormal(int vertexNum, DirectX::XMFLOAT3 normal)
{
	m_Normals[vertexNum] = normal;
}

void Mesh::SetUV(std::vector<DirectX::XMFLOAT2> uvs)
{
	m_UVs = uvs;
}

void My3DLib::Mesh::SetMaterialID(int materialID)
{
	m_MaterialID = materialID;
}
