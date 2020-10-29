#pragma once
#include <string>

class DebugLog {
public:
	static void Log(const std::string& logMessage);
	static void LogWarning(const std::string& warningMessage);
	static void LogError(const std::string& errorMessage);
};