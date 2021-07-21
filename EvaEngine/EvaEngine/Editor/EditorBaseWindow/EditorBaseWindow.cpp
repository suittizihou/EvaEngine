#include "EditorBaseWindow.h"
#include "../EditorWindowDataBase/EditorWindowDataBase.h"

using namespace EvaEngine::Editor::Internal;

EditorBaseWindow::EditorBaseWindow(const std::string& windowPath, EditorWindowDataBase* editorWindowDataBase) :
	EditorWindow(windowPath, ImGuiWindowFlags_MenuBar),
	p_EditorWindowDataBase{ editorWindowDataBase }
{
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

	//if (ImGui::BeginMenuBar()) {
	//	for (int i = 0; i < m_EditorWindowDataBase.size(); ++i) {
	//		if (ImGui::BeginMenu(m_EditorWindowDataBase[i]->windowPath[0].c_str())) {
	//			Scanning(m_EditorWindowDataBase[i], 1, 0);
	//			ImGui::EndMenu();
	//		}
	//	}
	//	ImGui::EndMenuBar();
	//}

	//if (ImGui::BeginMenuBar()) {
	//	if (ImGui::BeginMenu("Window")) {
	//		if (ImGui::MenuItem("Test")) {
	//		}
	//		ImGui::EndMenu();
	//	}
	//	ImGui::EndMenuBar();
	//}
}

void EditorBaseWindow::Scanning(std::weak_ptr<EditorWindowData> editorWindows) {
	
	for (auto editorWindow : editorWindows.lock()->childDatas) {
		if (editorWindow->childDatas.size() >= 1) {
			if (ImGui::BeginMenu(editorWindow->windowPath.c_str())) {
				Scanning(editorWindow);
				ImGui::EndMenu();
			}
		}
		else if(editorWindow->windowPath.size() >= 1) {
			if (ImGui::MenuItem(editorWindow->windowPath.c_str())) {
				for (auto window : editorWindow->editorWindows) {
					window->isOpen = true;
				}
			}
		}

		//if (ImGui::MenuItem(editorWindow->windowPath.c_str()))
		//{
		//	for (auto window : editorWindow->editorWindows) {
		//		window->isOpen = true;
		//	}

		//	//if (editorWindow->childDatas.size() >= 1) {
		//		if (ImGui::BeginMenu(editorWindow->windowPath.c_str())) {
		//			Scanning(editorWindow);
		//			ImGui::EndMenu();
		//		}
		//	//}
		//}
	}
		

	// ItemIndexとパスのサイズが同じ場合その場でWindowを表示
	//if (editorWindow->windowPath.size() == itemIndex) {
	//	if (ImGui::MenuItem(editorWindow->editorWindows[windowIndex]->GetWindowName().c_str())) {

	//		editorWindow->editorWindows[windowIndex]->isOpen = true;
	//		if (editorWindow->editorWindows.size() - 1 > windowIndex) {
	//			Scanning(editorWindow, itemIndex, windowIndex + 1);
	//		}
	//	}
	//}
	//else if (ImGui::MenuItem(editorWindow->windowPath[itemIndex].c_str())) {
	//	if (editorWindow->windowPath.size() - 1 == itemIndex) {
	//		editorWindow->editorWindows[windowIndex]->isOpen = true;
	//		if (editorWindow->editorWindows.size() - 1 > windowIndex) {
	//			Scanning(editorWindow, itemIndex, windowIndex + 1);
	//		}
	//	}
	//	else {
	//		Scanning(editorWindow, itemIndex + 1, windowIndex);
	//	}
	//}
}