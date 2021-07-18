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

				// ‰Šú‰»
				static HRESULT Init();

				// Editor•`‰æ‘O€”õ
				static void DrawBegin();
				// Editor•`‰æˆ—
				static void Draw();
				// Editor•`‰æI—¹
				static void DrawEnd();

				// EditorI—¹ˆ—
				static void End();

				static std::shared_ptr<SceneView> GetSceneView();

			private:
				// ImGui‚Ìİ’è‚ğs‚¤
				static HRESULT ImGuiSetting();

			private:
				static std::shared_ptr<SceneView> m_SceneView;
				static EvaEngine::Editor::Internal::EditorWindowDataBase m_EditorWindows;
			};
		}
	}
}
#endif