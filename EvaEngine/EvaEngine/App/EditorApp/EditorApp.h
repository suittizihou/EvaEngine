#if _DEBUG
#pragma once

#include <d3d11.h>
#include <wrl.h>
#include <memory>

namespace EvaEngine {
	namespace Editor {
		namespace Internal {
			class SceneView;
			class EditorCommand;

			class EditorApp {
			public:
				// ������
				static HRESULT Init();

				// Editor�`��O����
				static void DrawBegin();
				// Editor�`�揈��
				static void Draw(SceneView* sceneView, EditorCommand* editorCommand);
				// Editor�`��I����
				static void DrawEnd();

				// Editor�I��������
				static void End();

			private:
				// ImGui�̐ݒ���s��
				static HRESULT ImGuiSetting();

			private:
				static std::unique_ptr<SceneView> m_SceneView;
			};
		}
	}
}
#endif