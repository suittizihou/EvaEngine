#include "ConsoleWindow.h"
#include "../../../System/DebugLog/DebugLog.h"

using namespace EvaEngine::Editor;

ConsoleWindow::ConsoleWindow(const std::string& windowName, const std::string& windowPath) :
	EditorWindow(windowName, windowPath)
{

}

void ConsoleWindow::OnGUI()
{
	auto logs = DebugLog::GetLogDatas();
	for (int i = logs.size() - 1; i > 0; --i) {
		ImGui::Text(logs[i].message.c_str());
	}
}