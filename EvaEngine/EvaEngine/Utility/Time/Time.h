#pragma once

#include "TimeBase.h"

namespace EvaEngine {
	class Time {
		Time() = default;
		~Time() = default;
	public:
		static float GetDeltaTime() { return Internal::TimeBase::GetDeltaTime(); }
	};
}