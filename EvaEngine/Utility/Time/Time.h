#pragma once

#include "TimeBase.h"

#include "../../Define/DLLDefine.h"

static class Time {
public:
	static float GetDeltaTime() { return TimeBase::m_DeltaTime; }
};