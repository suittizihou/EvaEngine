#include "EditorBaseWindow.h"
#include "../EditorWindowDataBase/EditorWindowDataBase.h"

using namespace EvaEngine::Editor::Internal;

EditorBaseWindow::EditorBaseWindow(const std::string& windowPath, std::vector<std::shared_ptr<EditorWindowData>> editorWindowDataBase) :
	EditorWindow(windowPath, ImGuiWindowFlags_MenuBar),
	m_EditorWindowDataBase{ editorWindowDataBase }
{

}

void EditorBaseWindow::Begin() {
	Vector2 size = GetWindowSize();
	ImGui::SetNextWindowSize(ImVec2(size.x, size.y), ImGuiCond_FirstUseEver);
	ImGui::Begin(GetWindowName().c_str(), nullptr, windowFlags);
}

void EditorBaseWindow::OnGUI() {

	//if (ImGui::BeginMenuBar()) {
	//	if (ImGui::BeginMenu("File")) {
	//		ImGui::MenuItem("Console");
	//		ImGui::EndMenu();
	//	}
	//	if (ImGui::BeginMenu("Editor")) {
	//		ImGui::MenuItem("Build");
	//		ImGui::EndMenu();
	//	}
	//	ImGui::EndMenuBar();
	//}
}