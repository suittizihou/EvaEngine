#include "DebugLog.h"
#include <stdexcept>
#include <iostream>
#include <sstream>

using namespace EvaEngine;

std::vector<LogData> DebugLog::m_LogDatas;

void DebugLog::Log(const std::string& logMessage)
{
#if _DEBUG
	m_LogDatas.push_back(LogData(LogType::Normal, logMessage));
#endif
}
//
//void DebugLog::Log(void* logMessage)
//{
//#if _DEBUG
//	std::string text{};
//	std::istringstream iss(text);
//	iss >> logMessage;
//
//	m_LogDatas.push_back(LogData(LogType::Normal, iss.str()));
//#endif
//}

void DebugLog::LogWarning(const std::string& warningMessage)
{
#if _DEBUG
	m_LogDatas.push_back(LogData(LogType::Warning, warningMessage));
#endif
}

void DebugLog::LogError(const std::string& errorMessage)
{
#if _DEBUG
	m_LogDatas.push_back(LogData(LogType::Error, errorMessage));
#endif
}

std::vector<LogData> EvaEngine::DebugLog::GetLogDatas()
{
	return m_LogDatas;
}

void EvaEngine::DebugLog::ClearLog() {
	m_LogDatas.clear();
}