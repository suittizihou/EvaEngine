#pragma once

#include "../../Define/D3D11Defines.h"
#include <vector>
#include <DirectXMath.h>
#include "../ModelUtility/ModelData/VertexData.h"


namespace My3DLib {
	class Mesh {
	public:
		Mesh(int vertexSize = 0);

	public:
		// 頂点の数を設定
		void SetVertexNum(int vertexSize);
		// 頂点の構造体を設定
		void SetVertexData(std::vector<My3DLib::VertexData> vertexDatas, bool isCreateIndices = false);
		// 各頂点の座標を設定
		void SetVertexPos(int vertexNum, float x, float y, float z);
		// 各頂点の法線を設定
		void SetVertexNormal(int vertexNum, float x, float y, float z);
		// 各頂点の色を設定
		void SetVertexColor(int vertexNum, float r, float g, float b, float a);
		// 各頂点のUV座標を設定
		void SetVertexUV(int vertexNum, float u, float v);
		// 頂点バッファの設定
		void SetVertexBuffer(ID3D11Buffer* vertexBuffer);
		// 頂点を使用する順番の作成(インデックスバッファ)
		std::vector<UINT> CreateIndices(const std::vector<My3DLib::VertexData>& vertexDatas);
		// 頂点を使用する順番の設定(インデックスバッファ)
		void SetIndices(std::vector<unsigned int> indices);
		// インデックスバッファの設定
		void SetIndexBuffer(ID3D11Buffer* indexBuffer);
		// マテリアルIDの設定
		void SetMaterialID(UINT materialID);

		// 頂点情報の取得
		std::vector<My3DLib::VertexData> GetVertexData();
		// 頂点バッファーの取得
		ID3D11Buffer* const* GetVertexBuffer();
		// 頂点を使用する順番の取得(インデックスバッファ)
		std::vector<unsigned int> GetIndices();
		// インデックスバッファの取得
		ID3D11Buffer* GetIndexBuffer();
		// マテリアルIDの取得
		UINT GetMaterial();

	private:
		// 頂点データの配列
		std::vector<My3DLib::VertexData> m_Vertexs;
		// インデックスバッファ
		std::vector<unsigned int> m_Indices;
		// マテリアルID
		UINT m_MaterialID{};

		// GPU用頂点バッファー
		VertexBuffer m_VertexBuffer{ nullptr };
		// GPU用インデックスバッファ
		IndexBuffer m_IndexBuffer{ nullptr };
	};
}