#pragma once

#include <DirectXMath.h>

namespace EvaEngine {
	namespace Internal {
//#pragma pack(16)
		struct ConstantBufferData {
			DirectX::XMFLOAT4X4 world;				// ワールド行列
			DirectX::XMFLOAT4X4 view;				// ビュー行列
			DirectX::XMFLOAT4X4 projection;			// プロジェクション行列
			DirectX::XMFLOAT3	cameraPos;			// カメラ座標
			float pad1;
			DirectX::XMFLOAT3	lightDirection;		// ライトの向き
			float pad2;
			DirectX::XMFLOAT3   lightColor;			// ライトの色
			float pad3;
			DirectX::XMFLOAT3 ptPosition;			// ポイントライトの座標
			float pad4;
			DirectX::XMFLOAT3 ptColor;				// ポイントライトの色
			float ptRange;							// ポイントライトの影響範囲
			DirectX::XMFLOAT3	materialAmbient;	// 影の色
			//DirectX::XMFLOAT4	materialDiffuse;	// マテリアルの色
			//DirectX::XMFLOAT4	materialSpecular;	// つやの色
			float				shine = 5.0f;		// つや
		};
//#pragma pack()
	}
}