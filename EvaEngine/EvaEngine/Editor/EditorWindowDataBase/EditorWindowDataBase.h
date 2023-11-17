#pragma once
#if _DEBUG
#include <vector>
#include <memory>
#include <string>
#include "../../System/DebugLog/DebugLog.h"
#include "../EditorWindow/EditorWindow.h"
#include "../../Utility/StringAssist/StringAssist.h"
#include "../EditorBaseWindow/EditorBaseWindow.h"

namespace EvaEngine {
	namespace Editor {
		namespace Internal {

			class EditorWindowData {
			public:
				// パス(階層ごと)
				std::string windowPath;

				bool AddChildWindow(
					const std::vector<std::string> paths,
					const int pathIndex,
					const std::shared_ptr<EditorWindowBase> window) {

					// 階層名が違う場合リターン
					if (windowPath != paths[pathIndex]) return false;
					// 最後の階層なら追加
					if (paths.size() - 1 == pathIndex) { editorWindows.push_back(window); return true; }

					for (auto child : childDatas) {
						// 最後の階層でないなら更に階層を進む
						if (child->AddChildWindow(paths, pathIndex + 1, window)) {
							return true;
						}
					}

					// どれにも当てはまらない場合新しいものとして新規追加
					auto child = std::make_shared< EditorWindowData>();
					bool lastIndex = (paths.size() - 1 == pathIndex + 1);
					child->windowPath = paths[pathIndex + 1];
					if(lastIndex)  child->editorWindows.push_back(window);
					childDatas.push_back(child);
					
					// 最後の階層でないなら継続
					if(!lastIndex) child->AddChildWindow(paths, pathIndex + 1, window);

					return true;
				}

				// 子供の階層
				std::vector<std::shared_ptr<EditorWindowData>> childDatas;

				// この階層にあるEditorWindowを格納する
				std::vector<std::shared_ptr<Editor::EditorWindowBase>> editorWindows;
			};

			class EditorWindowDataBase {
			public:
				EditorWindowDataBase();
				~EditorWindowDataBase() = default;

				template<class T>
				void CreateEditorWindow(const std::string& windowPath) {
					static_assert(std::is_base_of<Editor::EditorWindowBase, T>::value == true, "The argument does not inherit from EditorWindowBase.");

					std::shared_ptr<Editor::EditorWindowBase> window = std::make_shared<T>(windowPath);
					std::vector<std::string> paths = StringAssist::Split(window->GetWindowPath(), "/");

					if (paths.size() <= 1) {
						DebugLog::LogError("Ignoring menu item Window because it is in no submenu!");
						return;
					}

					window->Init();

					// 同じパスなら同じ階層に追加
					for (int i = 0; i < m_EditorWindows.size(); ++i) 
					{
						// 親階層があればその子供に追加していく
						if (m_EditorWindows[i]->windowPath == paths[0]) {
							m_EditorWindows[i]->AddChildWindow(paths, 0, window);
							return;
						}
					}

					// 親階層が無ければ新しく追加
					std::shared_ptr<EditorWindowData> windowData = std::make_shared<EditorWindowData>();
					windowData->windowPath = paths[0];
					windowData->AddChildWindow(paths, 0, window);
					m_EditorWindows.push_back(windowData);
				}

				template<>
				void CreateEditorWindow<EditorBaseWindow>(const std::string& windowPath) {
					std::shared_ptr<Editor::EditorWindow<EditorBaseWindow>> window = std::make_shared<EditorBaseWindow>(windowPath, this);
					std::vector<std::string> paths = StringAssist::Split(window->GetWindowPath(), "/");

					// 既に登録済みであれば返す
					if (m_EditorWindows[0]->editorWindows.size() == 1) return;

					// 必ず最初に追加
					m_EditorWindows[0]->AddChildWindow(paths, 0, window);
				}

				void Draw();
				std::vector<std::shared_ptr<EditorWindowData>> GetEditorWindows();

			private:
				bool CheckEquals(const std::vector<std::string>& lhs, const std::vector<std::string>& rhs);
				void DrawWindow(const std::shared_ptr<EditorWindowData> editorWindowData) const;

			private:
				std::vector<std::string> m_ParentPaths{ "", "File", "Window", "Help" };
				std::vector<std::shared_ptr<EditorWindowData>> m_EditorWindows{};
			};
		}
	}
}
#endif