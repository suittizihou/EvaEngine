#if _DEBUG
#pragma once

#include <d3d11.h>
#include <wrl.h>
#include <memory>

#include "../../Editor/EditorWindowDataBase/EditorWindowDataBase.h"

namespace EvaEngine {
	class GameObject;
	class GameObjectDataBase;
	namespace Editor {
		namespace Internal {
			class SceneView;
			class EditorCommand;

			class EditorApp {
			public:
				EditorApp() = default;
				~EditorApp() = default;

				// 初期化
				static HRESULT Init();

				// Editorの更新処理
				static void Update();

				// Editor描画前準備
				static void DrawBegin();
				// Editor描画処理
				static void Draw();
				// Editor描画終了時
				static void DrawEnd();

				// Editor終了時処理
				static void End();

				static std::weak_ptr<EvaEngine::Editor::Internal::SceneView> GetSceneView();

			private:
				// ImGuiの設定を行う
				static HRESULT ImGuiSetting();

			private:
				static std::weak_ptr<EvaEngine::Editor::Internal::SceneView> m_SceneView;
				static EvaEngine::Editor::Internal::EditorWindowDataBase m_EditorWindows;
			};
		}
	}
}
#endif