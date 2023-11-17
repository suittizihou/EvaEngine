#if _DEBUG
#pragma once

#include "../../EditorWindow/EditorWindow.h"

namespace EvaEngine {
	namespace Editor {
		namespace Internal {
			class SceneWindow : public EditorWindow<SceneWindow> {
			public:
				SceneWindow(const std::string& windowPath);
				~SceneWindow() = default;

				void OnGUI() override;
			};
		}
	}
}
#endif