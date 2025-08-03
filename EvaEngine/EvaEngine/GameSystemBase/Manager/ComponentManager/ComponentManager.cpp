#include "ComponentManager.h"
#include "../../Base/GameObject/GameObject.h"

using namespace EvaEngine::Internal;

void ComponentManager::FixedUpdate(const std::u8string& sceneName)
{
	m_ComponentList[sceneName]->FixedUpdate();
}

void ComponentManager::Update(const std::u8string& sceneName)
{
	m_ComponentList[sceneName]->Update();
}

void EvaEngine::Internal::ComponentManager::ExecuteEditUpdate(const std::u8string& sceneName)
{
	m_ComponentList[sceneName]->ExecuteEditorUpdate();
}

void ComponentManager::LateUpdate(const std::u8string& sceneName)
{
	m_ComponentList[sceneName]->LateUpdate();
}

void ComponentManager::Draw(
	const std::u8string& sceneName,
	ID3D11DeviceContext* command)
{
	m_ComponentList[sceneName]->Draw(command);
}

#if _DEBUG
void ComponentManager::OnGUI(std::u8string& sceneName)
{
	m_ComponentList[sceneName]->OnGUI();
}
#endif

void ComponentManager::AddComponentDataBase(const std::u8string& sceneName)
{
	m_ComponentList[sceneName] = std::make_shared<ComponentDataBase>();
}

void ComponentManager::RemoveAllComponent(const std::u8string& sceneName)
{
	if (m_ComponentList.count(sceneName) == 0) return;
	m_ComponentList[sceneName]->RemoveAllComponent();
}

void EvaEngine::Internal::ComponentManager::RemoveAllComponent()
{
	for (const auto& componentList : m_ComponentList) {
		componentList.second->RemoveAllComponent();
	}
}
