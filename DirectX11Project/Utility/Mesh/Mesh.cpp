#include "Mesh.h"

using namespace My3DLib;

std::vector<Vector3> Mesh::GetVertices()
{
	return m_Vertices;
}

std::vector<unsigned int> Mesh::GetIndices()
{
	return m_Indices;
}

std::vector<Vector3> Mesh::GetNormal()
{
	return m_Normals;
}

std::vector<Vector2> Mesh::GetUV()
{
	return m_UVs;
}

void Mesh::SetVertices(std::vector<Vector3> vertices)
{
	m_Vertices = vertices;

	// –@üî•ñ‚Ì”‚ğ’¸“_‚Ì”‚Æ“¯‚¶‚É‚·‚é
	m_Normals.resize(m_Vertices.size());
}

void My3DLib::Mesh::SetVertexBuffer(ID3D11Buffer* vertexBuffer)
{
	m_VertexBuffer.Attach(vertexBuffer);
}

void Mesh::SetIndices(std::vector<unsigned int> indices)
{
	m_Indices = indices;
}

void My3DLib::Mesh::SetIndexBuffer(ID3D11Buffer* indexBuffer)
{
	m_IndexBuffer.Attach(indexBuffer);
}

void Mesh::SetNormals(std::vector<Vector3> normals)
{
	m_Normals = normals;
}

void Mesh::SetNormal(int vertexNum, Vector3 normal)
{
	m_Normals[vertexNum] = normal;
}

void Mesh::SetUV(std::vector<Vector2> uvs)
{
	m_UVs = uvs;
}
