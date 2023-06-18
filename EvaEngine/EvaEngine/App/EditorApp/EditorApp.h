#if _DEBUG
#pragma once

#include <d3d11.h>
#include <memory>
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib, "dxgi.lib")

#include "../../Editor/EditorWindowDataBase/EditorWindowDataBase.h"

namespace EvaEngine {
	class GameObject;
	class GameObjectDataBase;
	namespace Editor {
		namespace Internal {
			class SceneView;
			class EditorCommand;

			class EditorApp {
				EditorApp() = default;
				~EditorApp() = default;
			public:

				// ������
				static HRESULT Init();

				// Editor�̍X�V����
				static void Update();

				// Editor�`��O����
				static void DrawBegin();
				// Editor�`�揈��
				static void Draw();
				// Editor�`��I����
				static void DrawEnd();

				// Editor�I��������
				static void End();

				static std::weak_ptr<EvaEngine::Editor::Internal::SceneView> GetSceneView();

			private:
				// ImGui�̐ݒ���s��
				static HRESULT ImGuiSetting();

			private:
				static std::weak_ptr<EvaEngine::Editor::Internal::SceneView> m_SceneView;
				static EvaEngine::Editor::Internal::EditorWindowDataBase m_EditorWindows;
			};
		}
	}
}
#endif