#include "ComponentManager.h"
#include "../../Base/GameObject/GameObject.h"

using namespace EvaEngine;

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
	const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& command)
{
	m_ComponentList[sceneName]->Draw(command);
}

void EvaEngine::ComponentManager::DrawEditor(std::string& sceneName)
{
	m_ComponentList[sceneName]
}

void ComponentManager::AddComponentDataBase(const std::string& sceneName)
{
	m_ComponentList[sceneName] = std::make_shared<ComponentDataBase>();
}

void ComponentManager::RemoveAllComponent(const std::string& sceneName)
{
	m_ComponentList[sceneName]->RemoveAllComponent();
}
