#pragma once
#include "../EditorWindow/EditorWindow.h"

namespace EvaEngine {
	namespace Editor {
		namespace Internal {
			class EditorBaseWindow : public EditorWindow<EditorBaseWindow> {
			public:
				EditorBaseWindow(const std::string& windowPath);
				~EditorBaseWindow() = default;

				void Begin() override;
				void OnGUI() override;
			};
		}
	}
}