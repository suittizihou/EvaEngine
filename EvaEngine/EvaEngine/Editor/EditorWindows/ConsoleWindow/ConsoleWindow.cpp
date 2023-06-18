#if _DEBUG
#include "ConsoleWindow.h"
#include "../../../System/DebugLog/DebugLog.h"
#include <iostream>
#include <sstream>

using namespace EvaEngine::Editor::Internal;

ConsoleWindow::ConsoleWindow(const std::string& windowPath) :
	EditorWindow(windowPath)
{
}

void ConsoleWindow::OnGUI()
{
	auto logs = DebugLog::GetLogDatas();

	if (ImGui::Button("Clear")) {
		DebugLog::ClearLog();
	}
	ImGui::SameLine();
	if (ImGui::Button("Collapse")) {

	}
	ImGui::SameLine();
	if (ImGui::Button("Clear on Play")) {

	}
	ImGui::SameLine();
	if (ImGui::Button("Error Pause")) {

	}

	for (int i = static_cast<int>(logs.size()) - 1; i >= 0; --i) {
		auto log = logs[i];
		
		switch (log.logType) {

		case LogType::Normal:
			ImGui::TextColored(ImColor(1.0f, 1.0f, 1.0f), logs[i].message.c_str());
			break;

		case LogType::Warning:
			ImGui::TextColored(ImColor(1.0f, 1.0f, 0.0f), logs[i].message.c_str());
			break;

		default:
			ImGui::TextColored(ImColor(1.0f, 0.0f, 0.0f), logs[i].message.c_str());
			break;
		}
	}
}
#endif