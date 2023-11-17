#pragma once

namespace EvaEngine {
	class MainApp {
	private:
		MainApp() = default; 
		MainApp(const MainApp&);
		MainApp& operator=(const MainApp&);
		~MainApp() = default;

	public:
		static MainApp& Instance() {
			static MainApp instance{};
			return instance;
		}

		/// <summary>
		/// ウィンドウ、DirectX、ゲームエンジンの初期化を全部やる
		/// </summary>
		/// <returns></returns>
		bool Init();

		/// <summary>
		/// メインループに入る
		/// </summary>
		/// <returns></returns>
		int Run();
	};
}