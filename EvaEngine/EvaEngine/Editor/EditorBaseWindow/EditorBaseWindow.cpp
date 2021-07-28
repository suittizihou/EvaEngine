#include "EditorBaseWindow.h"
#include "../EditorWindowDataBase/EditorWindowDataBase.h"

using namespace EvaEngine::Editor::Internal;

EditorBaseWindow::EditorBaseWindow(const std::string& windowPath, EditorWindowDataBase* editorWindowDataBase) :
	EditorWindow(windowPath, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking),
	p_EditorWindowDataBase{ editorWindowDataBase }
{
	isOpen = true;
}

void EditorBaseWindow::Begin() {
	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(viewport->WorkSize);
	ImGui::SetNextWindowViewport(viewport->ID);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	ImGui::Begin(GetWindowName().c_str(), nullptr, windowFlags);
	ImGui::PopStyleVar();
	ImGui::PopStyleVar(2);
}

void EditorBaseWindow::OnGUI() {
	ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
	ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);

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