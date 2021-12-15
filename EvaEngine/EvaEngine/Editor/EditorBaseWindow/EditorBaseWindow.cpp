#if _DEBUG
#include "EditorBaseWindow.h"
#include "../../Setting/Window/Window.h"
#include "../EditorWindowDataBase/EditorWindowDataBase.h"
#include "../EditorApplication/EditorApplication.h"

using namespace EvaEngine::Editor;
using namespace EvaEngine::Editor::Internal;

EditorBaseWindow::EditorBaseWindow(const std::string& windowPath, EditorWindowDataBase* editorWindowDataBase) :
	EditorWindow(windowPath, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking),
	p_EditorWindowDataBase{ editorWindowDataBase }
{
	isOpen = true;
	windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
}

void EditorBaseWindow::Begin() {
	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(viewport->WorkSize);
	ImGui::SetNextWindowViewport(viewport->ID);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin(GetWindowName().c_str(), nullptr, windowFlags);
	ImGui::PopStyleVar();
	ImGui::PopStyleVar(2);
}

void EditorBaseWindow::OnGUI() {

	DrawPlayButtons();

	ImGuiID dockspace_id = ImGui::GetID("EditorDockSpace");
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

void EvaEngine::Editor::Internal::EditorBaseWindow::DrawPlayButtons()
{
	// ボタンをWindowの中心に
	ImVec2 cursor = ImGui::GetCursorPos();
	ImGui::InvisibleButton("##padded-text", ImVec2(EvaEngine::Internal::Window::GetViewport().Width / 2.0f, 24.0f));
	ImVec2 final_cursor_pos = ImGui::GetCursorPos();
	ImGui::SetCursorPos(ImVec2(cursor.x + EvaEngine::Internal::Window::GetViewport().Width / 2.0f, cursor.y + 2.0f));

	// 再生ボタン
	if (EditorApplication::isPlaying) ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.24f, 0.58f, 1.0f, 1.0f));
	else ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.3f, 0.3f, 0.3f, 1.0f));
	if (ImGui::Button("Play")) {
		EditorApplication::isPlaying = !EditorApplication::isPlaying;
		if(EditorApplication::isPlaying) ImGui::SetWindowFocus("GameWindow");
	}
	ImGui::PopStyleColor(1);

	// 一時停止ボタン
	if (EditorApplication::isPause) ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.24f, 0.58f, 1.0f, 1.0f));
	else ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.3f, 0.3f, 0.3f, 1.0f));
	ImGui::SameLine();
	if (ImGui::Button("Pause")) {
		EditorApplication::isPause = !EditorApplication::isPause;
		if (EditorApplication::isPause == false) ImGui::SetWindowFocus("GameWindow");
	}
	ImGui::PopStyleColor(1);

	// ステップボタン
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.3f, 0.3f, 0.3f, 1.0f));
	ImGui::SameLine();
	if (ImGui::Button("Step")) {
		if (EditorApplication::isPlaying) {
			EditorApplication::isPause = true;
			EditorApplication::Step();
		}
		ImGui::SetWindowFocus("GameWindow");
	}
	ImGui::PopStyleColor(1);

	ImGui::SetCursorPos(final_cursor_pos);	// ボタンをWindowの中心に
}

// 登録されたEditorWindowのパスをメニューに表示するため、再帰的に呼び出し
void EditorBaseWindow::Scanning(const std::weak_ptr<EditorWindowData>& editorWindows) {
	
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
#endif