#pragma once
#include <string>
#include <vector>
#include "../../Utility/StringAssist/StringAssist.h"

namespace EvaEngine {

	enum class LogType {
		Normal,
		Warning,
		Error
	};

	struct LogData {
		LogData(LogType logType, const std::u8string& message)
		{
			this->logType = logType;
			if (message.empty() == false)
			{
				this->message = message;
			}
		}
		~LogData() = default;

		LogType logType{};
		std::u8string message{};
	};

	class DebugLog {
		DebugLog() = default;
		~DebugLog() = default;
	public:
		static void Log(const std::u8string& logMessage);
		static void LogWarning(const std::u8string& warningMessage);
		static void LogError(const std::u8string& errorMessage);
		static void ShowErrorMessageWindow(const std::u8string& message);

		static std::vector<LogData> GetLogDatas();
		static void ClearLog();

	private:
		static std::vector<LogData> m_LogDatas;
	};
}