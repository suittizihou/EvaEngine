#pragma once

#include <DirectXMath.h>

namespace My3DLib {
	struct VertexData {
		DirectX::XMFLOAT3 position;		// 座標(x, y, z)
		DirectX::XMFLOAT3 normal;		// 法線
		DirectX::XMFLOAT4 color;		// 頂点カラー
		DirectX::XMFLOAT2 uv;		// テクスチャ座標(u, v)
	};
}