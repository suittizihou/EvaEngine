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
				// 初期化
				static HRESULT Init();

				// Editor描画前準備
				static void DrawBegin();
				// Editor描画処理
				static void Draw(SceneView* sceneView, EditorCommand* editorCommand);
				// Editor描画終了時
				static void DrawEnd();

				// Editor終了時処理
				static void End();

			private:
				// ImGuiの設定を行う
				static HRESULT ImGuiSetting();

			private:
				static std::unique_ptr<SceneView> m_SceneView;
			};
		}
	}
}
#endif