#pragma once

#include <d3d11.h>
#include <wrl.h>

#if _DEBUG
#include "../../Editor/EditorCommand/EditorCommand.h"
#include "../../Editor/SceneView/SceneView.h"
#endif

namespace EvaEngine {
	class EvaEngineApp {
	private:
		EvaEngineApp() = default;
		EvaEngineApp(const EvaEngineApp&);
		EvaEngineApp& operator=(const EvaEngineApp&);
		~EvaEngineApp();

	public:
		static EvaEngineApp& Instance() {
			static EvaEngineApp instance;
			return instance;
		}

		// ����������
		HRESULT Init();

		// �X�V����
		void Update();
		// �`�揈��
		void Draw(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& command);
		// Editor�֘A�̕`��
		void DrawEditor();
		// �t���[���I��������
		void FrameEnd();

		// �G���W���̏I��������
		void End();

#if _DEBUG
	private:
		SceneView m_SceneView{};
	};
#endif
}