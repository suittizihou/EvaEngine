#include "DebugLog.h"
#include "../../Setting/Window/Window.h"
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

void EvaEngine::DebugLog::ShowErrorMessageWindow(const std::string& message)
{
#if _DEBUG
	MessageBox(Internal::Window::g_hWnd, message.c_str(), TEXT("Error"), MB_OK);
#endif
}

std::vector<LogData> EvaEngine::DebugLog::GetLogDatas()
{
	return m_LogDatas;
}

void EvaEngine::DebugLog::ClearLog() {
	m_LogDatas.clear();
}