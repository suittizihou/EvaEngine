#include "EditorWindow.h"

using namespace EvaEngine::Editor;

EditorWindow::EditorWindow(const std::string& windowName, const std::string& windowPath) :
	m_WindowName{ windowName },
	m_WindowPath{ windowPath }
{
}

EditorWindow::~EditorWindow() {
	
}

void EvaEngine::Editor::EditorWindow::Begin()
{
	ImGui::Begin(m_WindowName.c_str());
}

void EvaEngine::Editor::EditorWindow::OnGUI() {

}

void EvaEngine::Editor::EditorWindow::End() {
	ImGui::End();
}