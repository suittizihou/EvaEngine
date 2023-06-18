#pragma once

#include <DirectXMath.h>

namespace EvaEngine {
	struct VertexData {
		DirectX::XMFLOAT3 position{};		// ���W(x, y, z)
		DirectX::XMFLOAT3 normal{};		// �@��
		DirectX::XMFLOAT4 color{ 1.0f, 1.0f, 1.0f, 1.0f };		// ���_�J���[
		DirectX::XMFLOAT2 uv{};		// �e�N�X�`�����W(u, v)
	};
}
