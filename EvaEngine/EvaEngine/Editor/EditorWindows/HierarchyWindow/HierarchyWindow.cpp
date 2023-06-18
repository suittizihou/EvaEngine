#if _DEBUG
#include "HierarchyWindow.h"
#include "../../../GameSystemBase/Manager/GameObjectManager/GameObjectManager.h"
#include "../../../GameSystemBase/Manager/ComponentManager/ComponentManager.h"
#include "../../../GameSystemBase/Manager/SceneManager/SceneManager.h"
#include "../../Selection/Selection.h"

using namespace EvaEngine;
using namespace EvaEngine::Internal;
using namespace EvaEngine::Editor::Internal;

void EvaEngine::Editor::Internal::HierarchyWindow::OnGUI()
{
	if (ImGui::TreeNodeEx(SceneManager::GetCurrentSceneName().c_str(), ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_SpanAvailWidth)) {
		std::vector<std::weak_ptr<GameObject>> gameObjects;
		GameObjectManager::Instance().GetGameObjectDataBase(SceneManager::GetCurrentSceneName()).lock()->GetAllGameObject(&gameObjects);

		m_ItemNum = 0;
		for (int i = 0; i < gameObjects.size(); ++i) {
			auto obj = gameObjects[i].lock();
			if (obj->GetTransform().lock()->parent().lock() == nullptr) {
				Scanning(obj);
			}
		}

		ImGui::TreePop();
	}
}

void EvaEngine::Editor::Internal::HierarchyWindow::Scanning(const std::shared_ptr<GameObject>& gameObject)
{
	m_ItemNum++;

	if (gameObject->GetTransform().lock()->get_child_count() <= 0) {

		ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_SpanAvailWidth;

		ImGui::TreeNodeEx((void*)(intptr_t)m_ItemNum, flags, gameObject->GetName().c_str());

		if (ImGui::IsItemClicked()) {
			Selection::SetActiveObject(gameObject);
		}

		return;
	}

	bool nodeOpen = ImGui::TreeNodeEx(
		(void*)(intptr_t)m_ItemNum,
		ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth,
		gameObject->GetName().c_str());

	if (ImGui::IsItemClicked())
	{
		Selection::SetActiveObject(gameObject);
	}

	if (nodeOpen) {
		for (const auto& child : gameObject->GetTransform().lock()->get_children()) {
			Scanning(child.lock()->GetGameObject().lock());
		}
		ImGui::TreePop();
	}
}

#endif