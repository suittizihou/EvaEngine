#ifndef TIME_H_
#define TIME_H_

#include "TimeBase.h"

static class Time {
public:
	static float GetDeltaTime() { return TimeBase::m_DeltaTime; }
};

#endif