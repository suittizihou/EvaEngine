#pragma once

#include <d3d11.h>
#include <wrl.h>

#if _DEBUG
#include "../../Editor/EditorCommand/EditorCommand.h"
#include "../../Editor/SceneView/SceneView.h"
#endif

namespace EvaEngine {
	namespace Internal {
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

			// 初期化処理
			HRESULT Init();

			// 更新処理
			void Update();
			// 描画処理
			void Draw(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& command);

#if _DEBUG
			// Editor関連の描画
			void DrawEditor();
#endif

			// フレーム終了時処理
			void FrameEnd();

			// エンジンの終了時処理
			void End();

#if _DEBUG
		private:
			EvaEngine::Editor::Internal::SceneView m_SceneView{};
#endif
		};
	}
}