#include "ComponentManager.h"
#include "../../Base/GameObject/GameObject.h"

void ComponentManager::FixedUpdate(const SceneType& sceneType)
{
	m_ComponentList[sceneType]->FixedUpdate();
}

void ComponentManager::Update(const SceneType& sceneType)
{
	m_ComponentList[sceneType]->FixedUpdate();
}

void ComponentManager::LateUpdate(const SceneType& sceneType)
{
	m_ComponentList[sceneType]->Update();
}

void ComponentManager::Draw(
	const SceneType& sceneType, 
	const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& command,
	const ModelApp& modelApp)
{
	m_ComponentList[sceneType]->Draw(command, modelApp);
}

void ComponentManager::AddComponentDataBase(const SceneType& sceneType)
{
	m_ComponentList[sceneType] = std::make_shared<ComponentDataBase>();
}

void ComponentManager::RunRemoveComponents(const SceneType& sceneType)
{
	m_ComponentList[sceneType]->RunRemoveComponents();
}

void ComponentManager::RemoveAllComponent(const SceneType& sceneType)
{
	m_ComponentList[sceneType]->RemoveAllComponent();
}
