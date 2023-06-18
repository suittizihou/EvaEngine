#pragma once

#include <DirectXMath.h>
#include "../../App/DirectX11App/DirectX11App.h"
#include "../ModelUtility/ModelData/ModelData.h"

namespace EvaEngine {
	namespace Internal {
		class BufferCreate {
			BufferCreate() = default;
			~BufferCreate() = default;
		public:
			// ���_�o�b�t�@�̍쐬
			static ID3D11Buffer* CreateVertexBuffer(const std::vector<VertexData>& vertices, size_t strides);
			// ���_�o�b�t�@���Z�b�g����
			static bool SetVertexBuffer(std::map<std::string, std::vector<Mesh>>& meshMap);
			// �C���f�b�N�X�o�b�t�@�̍쐬
			static ID3D11Buffer* CreateIndexBuffer(const std::vector<UINT>& indices, size_t strides);
			// �C���f�b�N�X�o�b�t�@���Z�b�g����
			static bool SetIndexBuffer(std::map<std::string, std::vector<Mesh>>& meshMap);
			// �萔�o�b�t�@�̍쐬
			static ID3D11Buffer* CreateConstantBuffer();
		};
	}
}