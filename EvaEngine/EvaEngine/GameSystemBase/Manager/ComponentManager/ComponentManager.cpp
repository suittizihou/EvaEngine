#include "ComponentManager.h"
#include "../../Base/GameObject/GameObject.h"

using namespace EvaEngine::Internal;

void ComponentManager::FixedUpdate(const std::string& sceneName)
{
	m_ComponentList[sceneName]->FixedUpdate();
}

void ComponentManager::Update(const std::string& sceneName)
{
	m_ComponentList[sceneName]->Update();
}

void ComponentManager::LateUpdate(const std::string& sceneName)
{
	m_ComponentList[sceneName]->LateUpdate();
}

void ComponentManager::Draw(
	const std::string& sceneName, 
	ID3D11DeviceContext* command)
{
	m_ComponentList[sceneName]->Draw(command);
}

#if _DEBUG
void ComponentManager::OnGUI(std::string& sceneName)
{
	m_ComponentList[sceneName]->OnGUI();
}
#endif

void ComponentManager::AddComponentDataBase(const std::string& sceneName)
{
	m_ComponentList[sceneName] = std::make_shared<ComponentDataBase>();
}

void ComponentManager::RemoveAllComponent(const std::string& sceneName)
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
