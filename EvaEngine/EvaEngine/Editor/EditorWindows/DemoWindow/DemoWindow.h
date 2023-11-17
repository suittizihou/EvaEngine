#if _DEBUG
#pragma once

#include "../../EditorWindow/EditorWindow.h"

namespace EvaEngine {
	namespace Editor {
		namespace Internal {
			class DemoWindow : public EditorWindow<DemoWindow> {
			public:
				DemoWindow(const std::string& windowPath) : EditorWindow<DemoWindow>(windowPath) {};
				~DemoWindow() = default;

				void Begin() override {};
				void OnGUI() override;
				void End() override {};

			private:
				bool m_Loaded{ false };
			};
		}
	}
}
#endif