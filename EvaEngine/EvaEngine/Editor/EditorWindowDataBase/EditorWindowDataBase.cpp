#include "EditorWindowDataBase.h"
#include "../EditorWindow/EditorWindow.h"

using namespace EvaEngine::Editor::Internal;

//std::vector<EditorWindowData> EditorWindowDataBase::m_EditorWindows;

EvaEngine::Editor::Internal::EditorWindowDataBase::EditorWindowDataBase()
{
	for (const auto& parentPath : m_ParentPaths) {
		auto windowData = std::make_shared<EditorWindowData>();
		windowData->windowPath = parentPath;
		m_EditorWindows.push_back(windowData);
	}
}

void EditorWindowDataBase::Draw() {
	for (const auto& windowData : m_EditorWindows) {
		for (const auto& window : windowData->editorWindows)
		{
			if (!window->isOpen) continue;

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