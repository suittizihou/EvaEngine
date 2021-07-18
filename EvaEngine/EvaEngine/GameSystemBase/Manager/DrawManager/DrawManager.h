#pragma once

#include "../../../Define/D3D11Defines.h"
#include "../../../Utility/ModelUtility/ModelData/ModelData.h"

namespace EvaEngine {

	class Camera;
	class Transform;

	namespace Internal {
		class DrawManager {
		public:
			// ������
			static HRESULT Init();

			// �`��J�n
			static void DrawBegin();
			// �`��
			static void Draw(
				const std::weak_ptr<Camera>& camera,
				const std::weak_ptr<Transform>& transform,
				ModelData* model);

			// �`��I��
			static void DrawEnd();

			// �}�e���A���̐ݒ�
			static void SetMaterial(Material* material);
			// ���_���C�A�E�g�̐ݒ�
			static void SetVertexLayout();

			// �V�F�[�_�[�̐ݒ�
			static void SetShader(Shader* shader);
			static void SetShader(Material* material);
			// �`�悷�邽�߂ɕK�v�ȏ����V�F�[�_�[���擾
			static Shader GetDefaultShader();

		private:
			static InputLayout m_InputLayout;
			static Shader m_Shader;
		};
	}
}