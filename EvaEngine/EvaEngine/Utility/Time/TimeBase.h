#pragma once
#include <chrono>

namespace EvaEngine {
	namespace Internal {
		class TimeBase {
			TimeBase() = default;
			~TimeBase() = default;
		public:
			// DeltaTime���Z�o����(���̎��ԂƑO�̎��ԂƂ̍������Z�o)
			static void UpdateDeltaTime();
			static float GetDeltaTime();

		private:
			static float m_DeltaTime;
			static std::chrono::system_clock::time_point m_PrevTime;
		};
	}
}