#if _DEBUG
#pragma once

#include <d3d11.h>
#include <wrl.h>
#include <memory>

#include "../../Editor/EditorWindowDataBase/EditorWindowDataBase.h"

namespace EvaEngine {
	namespace Editor {
		namespace Internal {
			class SceneView;
			class EditorCommand;

			class EditorApp {
			public:
				EditorApp() = default;
				~EditorApp() = default;

				// ������
				static HRESULT Init();

				// Editor�`��O����
				static void DrawBegin();
				// Editor�`�揈��
				static void Draw();
				// Editor�`��I����
				static void DrawEnd();

				// Editor�I��������
				static void End();

				static std::shared_ptr<SceneView> GetSceneView();

			private:
				// ImGui�̐ݒ���s��
				static HRESULT ImGuiSetting();

			private:
				static std::shared_ptr<SceneView> m_SceneView;
				static EvaEngine::Editor::Internal::EditorWindowDataBase m_EditorWindows;
			};
		}
	}
}
#endif