#pragma once
#include "../EditorWindow/EditorWindow.h"

namespace EvaEngine {
	namespace Editor {
		namespace Internal {

			class EditorWindowData;

			class EditorBaseWindow : public EditorWindow<EditorBaseWindow> {
			public:
				EditorBaseWindow(const std::string& windowPath, std::vector<std::weak_ptr<EditorWindowData>> editorWindowDataBase);
				~EditorBaseWindow() = default;

				void Begin() override;
				void OnGUI() override;

				void Scanning(std::weak_ptr<EditorWindowData> editorWindow);

			private:
				std::vector<std::weak_ptr<EditorWindowData>> m_EditorWindowDataBase{};
			};
		}
	}
}