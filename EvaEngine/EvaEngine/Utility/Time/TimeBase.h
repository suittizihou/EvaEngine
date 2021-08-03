#pragma once
#include <chrono>

namespace EvaEngine {
	namespace Internal {
		class TimeBase {
			TimeBase() = default;
			~TimeBase() = default;
		public:
			// DeltaTime‚ğZo‚·‚é(¡‚ÌŠÔ‚Æ‘O‚ÌŠÔ‚Æ‚Ì·•ª‚ğZo)
			static void UpdateDeltaTime();
			static float GetDeltaTime();

		private:
			static float m_DeltaTime;
			static std::chrono::system_clock::time_point m_PrevTime;
		};
	}
}