#pragma once

#include "../../Define/D3D11Defines.h"
#include "../ModelUtility/ModelData/ModelData.h"
#include <vector>
#include "../Math/Vector3/Vector3.h"
#include "../Math/Vector2/Vector2.h"

namespace My3DLib {
	class Mesh {
	public:
		// 頂点情報の取得
		std::vector<Vector3> GetVertices();
		// 頂点を使用する順番の取得(インデックスバッファ)
		std::vector<unsigned int> GetIndices();
		// 頂点の法線を取得
		std::vector<Vector3> GetNormal();
		// UVを取得
		std::vector<Vector2> GetUV();

		// 頂点情報をセット
		void SetVertices(std::vector<Vector3> vertices);
		void SetVertices(std::vector<My3DLib::ModelData::VertexData> vertices);
		void SetVertexBuffer(ID3D11Buffer* vertexBuffer);
		// 頂点を使用する順番のセット(インデックスバッファ)
		void SetIndices(std::vector<unsigned int> indices);
		void SetIndexBuffer(ID3D11Buffer* indexBuffer);
		// 頂点の法線をセット
		void SetNormals(std::vector<Vector3> normals);
		void SetNormal(int vertexNum, Vector3 normal);
		// UVのセット
		void SetUV(std::vector<Vector2> uvs);

	private:
		std::vector<Vector3> m_Vertices;
		std::vector<unsigned int> m_Indices;
		std::vector<Vector3> m_Normals;
		std::vector<Vector2> m_UVs;

		// GPU用頂点バッファー
		VertexBuffer m_VertexBuffer{ nullptr };
		// GPU用インデックスバッファ
		IndexBuffer m_IndexBuffer{ nullptr };
	};
}