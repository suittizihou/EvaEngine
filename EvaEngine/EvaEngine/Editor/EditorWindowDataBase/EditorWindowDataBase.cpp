#include "EditorWindowDataBase.h"
#include "../EditorWindow/EditorWindow.h"

std::vector<std::unique_ptr<EvaEngine::Editor::EditorWindow>> EvaEngine::Internal::EditorWindowDataBase::m_EditorWindows;

void EvaEngine::Internal::EditorWindowDataBase::Draw() {
	for (const auto& window : m_EditorWindows) {
		window->Begin();
		window->OnGUI();
		window->End();
	}
}