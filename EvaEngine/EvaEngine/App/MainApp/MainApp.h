#pragma once

#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#include <Windows.h>

namespace EvaEngine {
	namespace Internal {
		class MainApp {
		private:
			MainApp() = default;
			~MainApp() = default;
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