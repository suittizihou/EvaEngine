#pragma once

#include <d3d11.h>
#include <wrl.h>

namespace EvaEngine {
	namespace Internal {
		class EvaEngineApp {
		public:
			// 初期化処理
			static HRESULT Init();

			// 更新処理
			static void Update();
			// 描画処理
			static void Draw(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& command);

#if _DEBUG
			// Editor関連の更新
			static void UpdateEditor();
			// Editor関連の描画
			static void DrawEditor();
#endif

			// フレーム終了時処理
			static void FrameEnd();

			// エンジンの終了時処理
			static void End();
		};
	}
}