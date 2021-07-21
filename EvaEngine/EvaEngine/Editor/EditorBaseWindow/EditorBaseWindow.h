#pragma once
#include "../EditorWindow/EditorWindow.h"

namespace EvaEngine {
	namespace Editor {
		namespace Internal {

			class EditorWindowData;
			class EditorWindowDataBase;

			class EditorBaseWindow : public EditorWindow<EditorBaseWindow> {
			public:
				EditorBaseWindow(const std::string& windowPath, EditorWindowDataBase* editorWindowDataBase);
				~EditorBaseWindow() = default;

				void Begin() override;
				void OnGUI() override;

				void Scanning(std::weak_ptr<EditorWindowData> editorWindows);

			private:
				EditorWindowDataBase* p_EditorWindowDataBase{ nullptr };
			};
		}
	}
}