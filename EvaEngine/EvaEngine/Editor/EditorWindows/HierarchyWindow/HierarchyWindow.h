#if _DEBUG
#pragma once

#include "../../EditorWindow/EditorWindow.h"

namespace EvaEngine {
	class GameObject;
	namespace Editor {
		namespace Internal {
			class HierarchyWindow : public EditorWindow<HierarchyWindow> {
			public:
				HierarchyWindow(const std::string& path) : 
					EditorWindow<HierarchyWindow>(path) {}
				~HierarchyWindow() = default;

				void OnGUI() override;

			private:
				void Scanning(const std::shared_ptr<GameObject>& gameObject);
			
			private:
				int m_ItemNum{ 0 };
			};
		}
	}
}
#endif