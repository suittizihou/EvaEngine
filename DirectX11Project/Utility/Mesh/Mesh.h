#pragma once

#include "../../Define/D3D11Defines.h"
#include <vector>
#include <DirectXMath.h>
#include "../ModelUtility/ModelData/VertexData.h"


namespace My3DLib {
	class Mesh {
	public:
		// 頂点情報の取得
		std::vector<DirectX::XMFLOAT3> GetVertices();
		// 頂点バッファーの取得
		ID3D11Buffer* const* GetVertexBuffer();
		// 頂点を使用する順番の取得(インデックスバッファ)
		std::vector<unsigned int> GetIndices();
		// インデックスバッファの取得
		ID3D11Buffer* GetIndexBuffer();
		// 頂点の法線を取得
		std::vector<DirectX::XMFLOAT3> GetNormal();
		// UVを取得
		std::vector<DirectX::XMFLOAT2> GetUV();
		// マテリアルのIDを取得
		int GetMaterialID();

		// 頂点情報を設定
		void SetVertices(std::vector<DirectX::XMFLOAT3> vertices, bool isCreateIndices = false);
		void SetVertices(std::vector<My3DLib::VertexData> vertices, bool isCreateIndices = false);
		void SetVertexBuffer(ID3D11Buffer* vertexBuffer);
		//// 頂点を使用する順番の作成(インデックスバッファ)
		//void CreateIndices();
		// 頂点を使用する順番の設定(インデックスバッファ)
		void SetIndices(std::vector<unsigned int> indices);
		void SetIndexBuffer(ID3D11Buffer* indexBuffer);
		// 頂点の法線を設定
		void SetNormals(std::vector<DirectX::XMFLOAT3> normals);
		void SetNormal(int vertexNum, DirectX::XMFLOAT3 normal);
		// UVの設定
		void SetUV(std::vector<DirectX::XMFLOAT2> uvs);
		// マテリアルの番号を設定
		void SetMaterialID(int materialID);

	private:
		// 頂点の配列
		std::vector<DirectX::XMFLOAT3> m_Vertices;
		// 頂点を使う順番が記された配列
		std::vector<unsigned int> m_Indices;
		// それぞれの頂点の法線
		std::vector<DirectX::XMFLOAT3> m_Normals;
		// 頂点カラー
		std::vector<DirectX::XMFLOAT4> m_Color;
		// UV座標
		std::vector<DirectX::XMFLOAT2> m_UVs;
		// 振り分けられているマテリアルの番号
		int m_MaterialID{ 0 };

		// GPU用頂点バッファー
		VertexBuffer m_VertexBuffer{ nullptr };
		// GPU用インデックスバッファ
		IndexBuffer m_IndexBuffer{ nullptr };
	};
}