#if _DEBUG
#pragma once

namespace EvaEngine {
	namespace Editor {
		class EditorApplication {
			EditorApplication() = default;
			~EditorApplication() = default;
		public:
			static bool isPlaying;
			static bool isPause;

			static bool sceneWindowIsActive;
			static bool gameWindowIsActive;

			static bool isInputFreeze;

			// 現在のシーンを１フレームだけ進ませる
			static void Step();
		};
	}
}
#endif