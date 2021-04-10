#include "DebugLog.h"
#include <stdexcept>

using namespace EvaEngine;

void DebugLog::Log(const std::string& logMessage)
{
}

void DebugLog::LogWarning(const std::string& warningMessage)
{
}

void DebugLog::LogError(const std::string& errorMessage)
{
	throw std::runtime_error(errorMessage);
}
