#include "EditorWindowDataBase.h"
#include "../EditorWindow/EditorWindow.h"

std::vector<std::unique_ptr<EvaEngine::Editor::EditorWindow>> EvaEngine::Editor::Internal::EditorWindowDataBase::m_EditorWindows;

void EvaEngine::Editor::Internal::EditorWindowDataBase::Draw() {
	for (const auto& window : m_EditorWindows) {
		window->Begin();
		window->OnGUI();
		window->End();
	}
}