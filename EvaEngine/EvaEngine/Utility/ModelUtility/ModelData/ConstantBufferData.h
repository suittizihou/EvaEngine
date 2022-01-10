#pragma once

#include <DirectXMath.h>

namespace EvaEngine {
	namespace Internal {
//#pragma pack(16)
		struct ConstantBufferData {
			DirectX::XMFLOAT4X4 world;				// ���[���h�s��
			DirectX::XMFLOAT4X4 view;				// �r���[�s��
			DirectX::XMFLOAT4X4 projection;			// �v���W�F�N�V�����s��
			DirectX::XMFLOAT3	cameraPos;			// �J�������W
			float pad1;
			DirectX::XMFLOAT3	lightDirection;		// ���C�g�̌���
			float pad2;
			DirectX::XMFLOAT3   lightColor;			// ���C�g�̐F
			float pad3;
			DirectX::XMFLOAT3 ptPosition;			// �|�C���g���C�g�̍��W
			float pad4;
			DirectX::XMFLOAT3 ptColor;				// �|�C���g���C�g�̐F
			float ptRange;							// �|�C���g���C�g�̉e���͈�
			DirectX::XMFLOAT3	materialAmbient;	// �e�̐F
			//DirectX::XMFLOAT4	materialDiffuse;	// �}�e���A���̐F
			//DirectX::XMFLOAT4	materialSpecular;	// ��̐F
			float				shine = 5.0f;		// ��
		};
//#pragma pack()
	}
}