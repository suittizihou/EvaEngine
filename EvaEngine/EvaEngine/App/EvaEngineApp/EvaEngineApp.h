#pragma once

#include <d3d11.h>

namespace EvaEngine {
	namespace Internal {
		class EvaEngineApp {
			EvaEngineApp() = default;
			~EvaEngineApp() = default;
		public:
			// ����������
			static HRESULT Init();

			// �X�V����
			static void Update();
			// �`�揈��
			static void Draw(ID3D11DeviceContext* command);

#if _DEBUG
			// Editor�֘A�̍X�V
			static void UpdateEditor();
			// Editor�֘A�̕`��
			static void DrawEditor();
#endif

			// �t���[���I��������
			static void FrameEnd();

			// �G���W���̏I��������
			static void End();

		private:
			static void EditorUpdate();
			static void RuntimeUpdate();
		};
	}
}