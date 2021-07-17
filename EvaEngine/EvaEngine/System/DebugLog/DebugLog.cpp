#include "DebugLog.h"
#include <stdexcept>

using namespace EvaEngine;

std::vector<LogData> DebugLog::m_LogDatas;

void DebugLog::Log(const std::string& logMessage)
{
	m_LogDatas.push_back(LogData(LogType::Normal, logMessage));
}

void DebugLog::LogWarning(const std::string& warningMessage)
{
	m_LogDatas.push_back(LogData(LogType::Warning, warningMessage));
}

void DebugLog::LogError(const std::string& errorMessage)
{
	m_LogDatas.push_back(LogData(LogType::Error, errorMessage));
}

std::vector<LogData> EvaEngine::DebugLog::GetLogDatas()
{
	return m_LogDatas;
}
