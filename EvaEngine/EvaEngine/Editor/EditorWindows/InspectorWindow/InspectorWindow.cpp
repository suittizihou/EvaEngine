#if _DEBUG
#include "InspectorWindow.h"
#include "../../../GameSystemBase/Manager/GameObjectManager/GameObjectManager.h"
#include "../../../GameSystemBase/Manager/ComponentManager/ComponentManager.h"
#include "../../../GameSystemBase/Manager/SceneManager/SceneManager.h"
#include "../../Selection/Selection.h"

using namespace EvaEngine;
using namespace EvaEngine::Internal;

void EvaEngine::Editor::Internal::InspectorWindow::OnGUI()
{
	if (Selection::GetActiveObject().lock() != nullptr) {
		m_ItemNum = 0;

		std::vector<std::weak_ptr<Component>> components = Selection::GetActiveObject().lock()->GetAllComponents();
		for (const auto& component : components) {
			if (ImGui::TreeNodeEx((void*)(intptr_t)m_ItemNum, ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_OpenOnArrow, component.lock()->GetComponentName().c_str())) {
				component.lock()->OnGUI();
				ImGui::TreePop();
			}
			else {
				// ���Ă��鎞�Ă�
				component.lock()->OnClosedGUI();
			}
			m_ItemNum++;
		}
	}
}
#endif