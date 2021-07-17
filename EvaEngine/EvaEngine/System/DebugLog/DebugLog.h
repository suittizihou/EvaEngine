#pragma once
#include <string>
#include <vector>

namespace EvaEngine {

	enum class LogType {
		Normal,
		Warning,
		Error
	};

	struct LogData {
		LogData(LogType logType, const std::string& message) : 
			logType{ logType }, message{ message }{}
		~LogData() = default;

		LogType logType{};
		std::string message{};
	};

	class DebugLog {
	public:
		static void Log(const std::string& logMessage);
		static void LogWarning(const std::string& warningMessage);
		static void LogError(const std::string& errorMessage);

		static std::vector<LogData> GetLogDatas();
		static void ClearLog();

	private:
		static std::vector<LogData> m_LogDatas;
	};
}