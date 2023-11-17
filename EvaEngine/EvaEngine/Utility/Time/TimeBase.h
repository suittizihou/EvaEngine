#pragma once
#include <chrono>

namespace EvaEngine {
	namespace Internal {
		class TimeBase {
			TimeBase() = default;
			~TimeBase() = default;
		public:
			// DeltaTimeを算出する(今の時間と前の時間との差分を算出)
			static void UpdateDeltaTime();
			static float GetDeltaTime();

		private:
			static float m_DeltaTime;
			static std::chrono::system_clock::time_point m_PrevTime;
		};
	}
}