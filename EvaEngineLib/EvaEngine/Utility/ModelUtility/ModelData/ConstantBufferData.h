#pragma once

#include <DirectXMath.h>

namespace EvaEngine {
	struct ConstantBufferData {
		DirectX::XMFLOAT4X4 world;				// ワールド行列
		DirectX::XMFLOAT4X4 view;				// ビュー行列
		DirectX::XMFLOAT4X4 projection;			// プロジェクション行列
		DirectX::XMFLOAT4	cameraPos;			// カメラ座標
		DirectX::XMFLOAT4	lightVector;		// ライトの向き
		DirectX::XMFLOAT4   lightColor;			// ライトの色
		DirectX::XMFLOAT4	materialAmbient;	// マテリアルの影の色
		DirectX::XMFLOAT4	materialDiffuse;	// マテリアルの色
		DirectX::XMFLOAT4	materialSpecular;	// マテリアルのつや
	};
}