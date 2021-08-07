#pragma once

#include "../../EditorWindow/EditorWindow.h"

namespace EvaEngine {
	namespace Editor {
		namespace Internal {
			class InspectorWindow : public EditorWindow<InspectorWindow> {
			public:
				InspectorWindow(const std::string& windowPath) : 
					EditorWindow<InspectorWindow>(windowPath) {};
				~InspectorWindow() = default;
				
				void OnGUI() override;

			private:
				int m_ItemNum{ 0 };
				bool isFirstOpen{ false };
			};
		}
	}
}