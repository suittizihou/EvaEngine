#if _DEBUG
#pragma once

#include "../../EditorWindow/EditorWindow.h"

namespace EvaEngine {
	namespace Editor {
		namespace Internal {
			class ProjectWindow : public EditorWindow<ProjectWindow> {
			public:
				ProjectWindow(const std::u8string& windowPath) :
					EditorWindow<ProjectWindow>(windowPath) {}
				~ProjectWindow() = default;

				void OnGUI() override;
			};
		}
	}
}
#endif