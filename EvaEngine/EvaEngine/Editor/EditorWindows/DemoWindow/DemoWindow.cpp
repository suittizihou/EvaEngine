#include "DemoWindow.h"

void EvaEngine::Editor::Internal::DemoWindow::OnGUI()
{
	ImGui::ShowDemoWindow(&isOpen, &m_Loaded);
}