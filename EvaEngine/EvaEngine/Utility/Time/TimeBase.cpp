#include "TimeBase.h"
#include <chrono>

float EvaEngine::Internal::TimeBase::m_DeltaTime{};
std::chrono::system_clock::time_point EvaEngine::Internal::TimeBase::m_PrevTime{};

void EvaEngine::Internal::TimeBase::UpdateDeltaTime()
{
	auto currentTime = std::chrono::system_clock::now();
	auto difference = currentTime - m_PrevTime;
	m_PrevTime = currentTime;

	m_DeltaTime = (std::chrono::duration_cast<std::chrono::milliseconds>(difference).count() / 1000.0f);
}

float EvaEngine::Internal::TimeBase::GetDeltaTime()
{
	return m_DeltaTime;
}