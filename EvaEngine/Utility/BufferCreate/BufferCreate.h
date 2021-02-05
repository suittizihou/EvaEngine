#pragma once

#include <DirectXMath.h>
#include "../../App/DirectX11App/DirectX11App.h"
#include "../ModelUtility/ModelData/ModelData.h"

#ifdef EVAENGINE_EXPORTS
#define EVAENGINE_API __declspec(dllexport)
#else
#define EVAENGINE_API __declspec(dllimport)
#endif

EVAENGINE_API class BufferCreate {
public:
	// ���_�o�b�t�@�̍쐬
	static ID3D11Buffer* CreateVertexBuffer(const std::vector<My3DLib::VertexData>& vertices, size_t strides);
	// ���_�o�b�t�@���Z�b�g����
	static bool SetVertexBuffer(std::map<std::string, std::vector<My3DLib::Mesh>>& meshMap);
	// �C���f�b�N�X�o�b�t�@�̍쐬
	static ID3D11Buffer* CreateIndexBuffer(const std::vector<UINT>& indices, size_t strides);
	// �C���f�b�N�X�o�b�t�@���Z�b�g����
	static bool SetIndexBuffer(std::map<std::string, std::vector<My3DLib::Mesh>>& meshMap);
	// �萔�o�b�t�@�̍쐬
	static ID3D11Buffer* CreateConstantBuffer();
};