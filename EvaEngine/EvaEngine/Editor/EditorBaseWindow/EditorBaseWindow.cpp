#include "EditorBaseWindow.h"
#include "../EditorWindowDataBase/EditorWindowDataBase.h"

using namespace EvaEngine::Editor::Internal;

EditorBaseWindow::EditorBaseWindow(const std::string& windowPath, EditorWindowDataBase* editorWindowDataBase) :
	EditorWindow(windowPath, ImGuiWindowFlags_MenuBar),
	p_EditorWindowDataBase{ editorWindowDataBase }
{
	//windowFlags |= 
	//	ImGuiWindowFlags_NoTitleBar |
	//	ImGuiWindowFlags_NoCollapse |
	//	ImGuiWindowFlags_NoResize |
	//	ImGuiWindowFlags_NoMove |
	//	ImGuiWindowFlags_NoBringToFrontOnFocus |
	//	ImGuiWindowFlags_NoNavFocus;

	isOpen = true;
}

void EditorBaseWindow::Begin() {
	Vector2 size = GetWindowSize();
	ImGui::SetNextWindowSize(ImVec2(size.x, size.y), ImGuiCond_FirstUseEver);
	ImGui::Begin(GetWindowName().c_str(), nullptr, windowFlags);
}

void EditorBaseWindow::OnGUI() {

	if (ImGui::BeginMenuBar()) {
		for (auto windowData : p_EditorWindowDataBase->GetEditorWindows()) {
			if (windowData->windowPath.size() == 0) continue;

			if (ImGui::BeginMenu(windowData->windowPath.c_str())) {
					Scanning(windowData);
				ImGui::EndMenu();
			}
		}
		ImGui::EndMenuBar();
	}
}

void EditorBaseWindow::Scanning(std::weak_ptr<EditorWindowData> editorWindows) {
	
	for (auto editorWindow : editorWindows.lock()->childDatas) {
		if (editorWindow->childDatas.size() >= 1) {
			if (ImGui::BeginMenu(editorWindow->windowPath.c_str())) {
				Scanning(editorWindow);
				ImGui::EndMenu();
			}
		}
		else if (editorWindow->windowPath.size() >= 1) {
			if (ImGui::MenuItem(editorWindow->windowPath.c_str())) {
				for (auto window : editorWindow->editorWindows) {
					window->isOpen = true;
				}
			}
		}
	}
}