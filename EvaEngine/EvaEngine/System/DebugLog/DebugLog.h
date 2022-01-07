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
		LogData(LogType logType, const std::string& message)
		{
			this->logType = logType;
			if (message.empty() == false) EvaEngine::StringAssist::ToUTF8(message, this->message);
		}
		~LogData() = default;

		LogType logType{};
		std::string message{};
	};

	class DebugLog {
		DebugLog() = default;
		~DebugLog() = default;
	public:
		static inline void Log(const std::string& logMessage);
		static inline void LogWarning(const std::string& warningMessage);
		static inline void LogError(const std::string& errorMessage);

		static std::vector<LogData> GetLogDatas();
		static void ClearLog();

	private:
		static std::vector<LogData> m_LogDatas;
	};
}