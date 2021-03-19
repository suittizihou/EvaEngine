#pragma once

#include "TimeBase.h"

static class Time {
public:
	static float GetDeltaTime() { return TimeBase::m_DeltaTime; }
};