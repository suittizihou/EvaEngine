#pragma once

#include <DirectXMath.h>

#include "../../Math/Matrix4x4/Matrix4x4.h"
#include "../../Math/Vector3/Vector3.h"

namespace EvaEngine {
	namespace Internal {
//#pragma pack(16)
		struct ConstantBufferData {
			Matrix4x4 world;				// ワールド行列
			Matrix4x4 view;				// ビュー行列
			Matrix4x4 projection;			// プロジェクション行列
			Vector3	cameraPos;			// カメラ座標
			float pad1;
			Vector3	lightDirection;		// ライトの向き
			float pad2;
			Vector3   lightColor;			// ライトの色
			float pad3;
			Vector3 ptPosition;			// ポイントライトの座標
			float pad4;
			Vector3 ptColor;				// ポイントライトの色
			float ptRange;							// ポイントライトの影響範囲
			Vector3 spPosition;
			float pad5;
			Vector3 spColor;
			float spRange;
			Vector3 spDirection;
			float spAngle;
			Vector3	materialAmbient;	// 影の色
			float shine = 20.0f;		// つや
		};
//#pragma pack()
	}
}