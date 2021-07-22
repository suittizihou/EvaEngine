#pragma once
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

			struct EditorWindowData {
				// ƒpƒX(ŠK‘w‚²‚Æ)
				std::string windowPath;

				bool AddChildWindow(
					const std::vector<std::string> paths,
					const int pathIndex,
					const std::shared_ptr<EditorWindowBase> window) {

					// ŠK‘w–¼‚ªˆá‚¤ê‡ƒŠƒ^[ƒ“
					if (windowPath != paths[pathIndex]) return false;
					// ÅŒã‚ÌŠK‘w‚È‚ç’Ç‰Á
					if (paths.size() - 1 == pathIndex) { editorWindows.push_back(window); return true; }

					for (auto child : childDatas) {
						// ÅŒã‚ÌŠK‘w‚Å‚È‚¢‚È‚çX‚ÉŠK‘w‚ği‚Ş
						if (child->AddChildWindow(paths, pathIndex + 1, window)) {
							return true;
						}
					}

					// ‚Ç‚ê‚É‚à“–‚Ä‚Í‚Ü‚ç‚È‚¢ê‡V‚µ‚¢‚à‚Ì‚Æ‚µ‚ÄV‹K’Ç‰Á
					auto child = std::make_shared< EditorWindowData>();
					bool lastIndex = (paths.size() - 1 == pathIndex + 1);
					child->windowPath = paths[pathIndex + 1];
					if(lastIndex)  child->editorWindows.push_back(window);
					childDatas.push_back(child);
					
					// ÅŒã‚ÌŠK‘w‚Å‚È‚¢‚È‚çŒp‘±
					if(!lastIndex) child->AddChildWindow(paths, pathIndex + 1, window);

					return true;
				}

				// q‹Ÿ‚ÌŠK‘w
				std::vector<std::shared_ptr<EditorWindowData>> childDatas;

				// ‚±‚ÌŠK‘w‚É‚ ‚éEditorWindow‚ğŠi”[‚·‚é
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
						DebugLog::LogError(u8"Ignoring menu item Window because it is in no submenu!");
						return;
					}

					// “¯‚¶ƒpƒX‚È‚ç“¯‚¶ŠK‘w‚É’Ç‰Á
					for (int i = 0; i < m_EditorWindows.size(); ++i) 
					{
						// eŠK‘w‚ª‚ ‚ê‚Î‚»‚Ìq‹Ÿ‚É’Ç‰Á‚µ‚Ä‚¢‚­
						if (m_EditorWindows[i]->windowPath == paths[0]) {
							m_EditorWindows[i]->AddChildWindow(paths, 0, window);
							return;
						}
					}

					// eŠK‘w‚ª–³‚¯‚ê‚ÎV‚µ‚­’Ç‰Á
					std::shared_ptr<EditorWindowData> windowData = std::make_shared<EditorWindowData>();
					windowData->windowPath = paths[0];
					window->AddChildWindow(paths, 0, window);
					m_EditorWindows.push_back(windowData);
				}

				template<>
				void CreateEditorWindow<EditorBaseWindow>(const std::string& windowPath) {
					std::shared_ptr<Editor::EditorWindow<EditorBaseWindow>> window = std::make_shared<EditorBaseWindow>(windowPath, this);
					std::vector<std::string> paths = StringAssist::Split(window->GetWindowPath(), "/");

					// “¯‚¶ŠK‘w‚ª–³‚¯‚ê‚ÎV‚µ‚­’Ç‰Á
					std::shared_ptr<EditorWindowData> windowData = std::make_shared<EditorWindowData>();
					windowData->windowPath = paths[0];
					windowData->editorWindows.push_back(window);
					m_EditorWindows.push_back(windowData);
				}

				void Draw();
				std::vector<std::shared_ptr<EditorWindowData>> GetEditorWindows();

			private:
				bool CheckEquals(const std::vector<std::string>& lhs, const std::vector<std::string>& rhs);
				void DrawWindow(const std::shared_ptr<EditorWindowData> editorWindowData) const;

			private:
				std::vector<std::string> m_ParentPaths{ "File", "Window" };
				std::vector<std::shared_ptr<EditorWindowData>> m_EditorWindows{};
			};
		}
	}
}