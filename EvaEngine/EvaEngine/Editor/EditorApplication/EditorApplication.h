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

			// ���݂̃V�[�����P�t���[�������i�܂���
			static void Step();
		};
	}
}
#endif