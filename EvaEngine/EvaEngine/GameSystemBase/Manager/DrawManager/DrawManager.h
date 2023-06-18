#pragma once

#include "../../../Define/D3D11Defines.h"
#include "../../../Utility/ModelUtility/ModelData/ModelData.h"

namespace EvaEngine {

	class Camera;
	class Transform;

	namespace Internal {
		class DrawManager {
			DrawManager() = default;
			~DrawManager() = default;
		public:
			// ������
			static HRESULT Init();

			// �`��J�n
			static void DrawBegin(const std::weak_ptr<Camera>& camera);
			// �`��
			static void Draw(
				const std::weak_ptr<Camera>& camera,
				const std::weak_ptr<Transform>& transform,
				const std::weak_ptr<ModelData>& model);

			// �`��I��
			static void DrawEnd();

			// �}�e���A���̐ݒ�
			static void SetMaterial(Material* material);

			// �V�F�[�_�[�̐ݒ�
			static void SetShader(Shader* shader);
			static void SetShader(Material* material);
			// �`�悷�邽�߂ɕK�v�ȏ����V�F�[�_�[���擾
			static Shader GetDefaultShader();

		private:
			static Shader m_Shader;
		};
	}
}