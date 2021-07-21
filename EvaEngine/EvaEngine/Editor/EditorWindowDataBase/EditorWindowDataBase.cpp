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
		DrawWindow(windowData);
	}
}

std::vector<std::shared_ptr<EditorWindowData>> EvaEngine::Editor::Internal::EditorWindowDataBase::GetEditorWindows()
{
	return m_EditorWindows;
}

void EvaEngine::Editor::Internal::EditorWindowDataBase::DrawWindow(const std::shared_ptr<EditorWindowData> editorWindowData) const
{
	for (const auto& window : editorWindowData->editorWindows)
	{
		if (!window->isOpen) continue;

		window->Begin();
		window->OnGUI();
		window->End();
	}

	for (const auto& child : editorWindowData->childDatas) {
		DrawWindow(child);
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