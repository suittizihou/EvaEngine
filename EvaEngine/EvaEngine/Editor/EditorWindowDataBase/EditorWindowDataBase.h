#pragma once
#include <vector>
#include <memory>
#include <string>
#include "../EditorWindow/EditorWindow.h"
#include "../../Utility/StringAssist/StringAssist.h"
#include "../EditorBaseWindow/EditorBaseWindow.h"

namespace EvaEngine {
	namespace Editor {
		namespace Internal {

			struct EditorWindowData {
				// �p�X�𕪊����ē����
				std::vector<std::string> windowPaths;
				// EditorWindow���i�[����
				std::vector<std::shared_ptr<Editor::EditorWindowBase>> editorWindow;
			};

			class EditorWindowDataBase {
			public:
				EditorWindowDataBase() = default;
				~EditorWindowDataBase() = default;

				template<class T>
				void CreateEditorWindow(const std::string& windowPath) {
					static_assert(std::is_base_of<Editor::EditorWindow<T>, T>::value == true, "The argument does not inherit from EditorWindow.");

					std::shared_ptr<Editor::EditorWindow<T>> window = std::make_shared<T>(windowPath);
					std::vector<std::string> paths = StringAssist::Split(window->GetWindowPath(), '/');

					// �����p�X�Ȃ瓯���K�w�ɒǉ�
					for (int i = 0; i < m_EditorWindows.size(); ++i) 
					{
						// �p�X���������`�F�b�N
						if (CheckEquals(m_EditorWindows[i]->windowPaths, paths)) {
							m_EditorWindows[i]->editorWindow.push_back(window);
							return;
						}
					}

					//// �����K�w��������ΐV�����ǉ�
					std::shared_ptr<EditorWindowData> windowData = std::make_shared<EditorWindowData>();
					windowData->windowPaths = paths;
					windowData->editorWindow.push_back(window);
					m_EditorWindows.push_back(windowData);
				}

				template<>
				void CreateEditorWindow<EditorBaseWindow>(const std::string& windowPath) {
					std::shared_ptr<Editor::EditorWindow<EditorBaseWindow>> window = std::make_shared<EditorBaseWindow>(windowPath, m_EditorWindows);
					std::vector<std::string> paths = StringAssist::Split(window->GetWindowPath(), '/');

					// �����K�w��������ΐV�����ǉ�
					std::shared_ptr<EditorWindowData> windowData = std::make_shared<EditorWindowData>();
					windowData->windowPaths = paths;
					windowData->editorWindow.push_back(window);
					m_EditorWindows.push_back(windowData);
				}

				void Draw();

			private:
				bool CheckEquals(const std::vector<std::string>& lhs, const std::vector<std::string>& rhs);

			private:
				std::vector<std::shared_ptr<EditorWindowData>> m_EditorWindows{};
			};
		}
	}
}