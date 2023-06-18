#pragma once

#include <DirectXMath.h>

#include "../../Math/Matrix4x4/Matrix4x4.h"
#include "../../Math/Vector3/Vector3.h"

namespace EvaEngine {
	namespace Internal {
//#pragma pack(16)
		struct ConstantBufferData {
			Matrix4x4 world;				// ���[���h�s��
			Matrix4x4 view;				// �r���[�s��
			Matrix4x4 projection;			// �v���W�F�N�V�����s��
			Vector3	cameraPos;			// �J�������W
			float pad1;
			Vector3	lightDirection;		// ���C�g�̌���
			float pad2;
			Vector3   lightColor;			// ���C�g�̐F
			float pad3;
			Vector3 ptPosition;			// �|�C���g���C�g�̍��W
			float pad4;
			Vector3 ptColor;				// �|�C���g���C�g�̐F
			float ptRange;							// �|�C���g���C�g�̉e���͈�
			Vector3 spPosition;
			float pad5;
			Vector3 spColor;
			float spRange;
			Vector3 spDirection;
			float spAngle;
			Vector3	materialAmbient;	// �e�̐F
			float shine = 20.0f;		// ��
		};
//#pragma pack()
	}
}