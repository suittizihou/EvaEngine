#pragma once

#include <Windows.h>

namespace EvaEngine {
	namespace Internal {
		class MainApp {
		private:
		public:
			/// <summary>
			/// ウィンドウ、DirectX、ゲームエンジンの初期化を全部やる
			/// </summary>
			/// <returns></returns>
			static HRESULT Init();

			/// <summary>
			/// メインループに入る
			/// </summary>
			/// <returns></returns>
			static int Run();
		};
	}
}