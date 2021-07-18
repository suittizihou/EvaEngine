#pragma once

#include <DirectXMath.h>

namespace EvaEngine {
	namespace Internal {
		struct ConstantBufferData {
			DirectX::XMFLOAT4X4 world;				// ���[���h�s��
			DirectX::XMFLOAT4X4 view;				// �r���[�s��
			DirectX::XMFLOAT4X4 projection;			// �v���W�F�N�V�����s��
			DirectX::XMFLOAT4	cameraPos;			// �J�������W
			DirectX::XMFLOAT4	lightVector;		// ���C�g�̌���
			DirectX::XMFLOAT4   lightColor;			// ���C�g�̐F
			DirectX::XMFLOAT4	materialAmbient;	// �}�e���A���̉e�̐F
			DirectX::XMFLOAT4	materialDiffuse;	// �}�e���A���̐F
			DirectX::XMFLOAT4	materialSpecular;	// �}�e���A���̂�
		};
	}
}