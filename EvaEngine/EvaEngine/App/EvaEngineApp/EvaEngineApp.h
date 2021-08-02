#pragma once

#include <d3d11.h>
#include <wrl.h>

namespace EvaEngine {
	namespace Internal {
		class EvaEngineApp {
		public:
			// ����������
			static HRESULT Init();

			// �X�V����
			static void Update();
			// �`�揈��
			static void Draw(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& command);

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
		};
	}
}