#pragma once

#include <DirectXMath.h>

namespace EvaEngine {
	struct VertexData {
		DirectX::XMFLOAT3 position{};		// 座標(x, y, z)
		DirectX::XMFLOAT3 normal{};		// 法線
		DirectX::XMFLOAT4 color{ 1.0f, 1.0f, 1.0f, 1.0f };		// 頂点カラー
		DirectX::XMFLOAT2 uv{};		// テクスチャ座標(u, v)
	};
}