#pragma once
#include <vector>
#include <memory>
#include <string>

#undef CreateWindow

namespace EvaEngine {
	namespace Editor {
		class EditorWindow;

		namespace Internal {
			class EditorWindowDataBase {
			public:
				EditorWindowDataBase() = default;
				~EditorWindowDataBase() = default;

				template<class T>
				static void CreateWindow(const std::string& windowName, const std::string& windowPath) {
					static_assert(std::is_base_of<Editor::EditorWindow, T>::value == true, "The argument does not inherit from EditorWindow.");
					m_EditorWindows.push_back(std::make_unique<T>(windowName, windowPath));
				}

				static void Draw();

			private:
				static std::vector<std::unique_ptr<Editor::EditorWindow>> m_EditorWindows;
			};
		}
	}
}