#pragma once

#include "../../../Define/D3D11Defines.h"

class Material;

class DrawManager {
public:
	// 頂点レイアウトのセット
	static void SetInputLayout(ID3D11InputLayout* vertexLayout);
	// シェーダーのセット
	static void SetShader(const Material& material);

	// 頂点バッファーのセット
	static void SetVertexBuffer(ID3D11Buffer* vertexBuffer, UINT vertexSize);
	// インデックスバッファーのセット
	static void SetIndexBuffer(ID3D11Buffer* indexBuffer);

	// 描画開始
	static void DrawBegin();
	// 描画終了
	static void DrawEnd();

	// プリミティブの描画
	static void DrawIndexed(UINT vertexNum);
};