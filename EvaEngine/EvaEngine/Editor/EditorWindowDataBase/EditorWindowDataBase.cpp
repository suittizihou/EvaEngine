#include "EditorWindowDataBase.h"
#include "../EditorWindow/EditorWindow.h"

using namespace EvaEngine::Editor::Internal;

//std::vector<EditorWindowData> EditorWindowDataBase::m_EditorWindows;

void EditorWindowDataBase::Draw() {
	for (const auto& windowData : m_EditorWindows) {
		for (const auto& window : windowData->editorWindow)
		{
			if (!window->IsOpen()) continue;

			window->Begin();
			window->OnGUI();
			window->End();
		}
	}
}

bool EditorWindowDataBase::CheckEquals(const std::vector<std::string>& lhs, const std::vector<std::string>& rhs) {
	if (lhs.size() == rhs.size()) {
		for (int i = 0; i < lhs.size(); ++i) {
			if (lhs[i] != rhs[i]) {
				return false;
			}
		}
	}
	return true;
}