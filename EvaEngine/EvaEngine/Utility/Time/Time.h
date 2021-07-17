#pragma once

#include "TimeBase.h"

namespace EvaEngine {
	class Time {
	public:
		static float GetDeltaTime() { return Internal::TimeBase::GetDeltaTime(); }
	};
}