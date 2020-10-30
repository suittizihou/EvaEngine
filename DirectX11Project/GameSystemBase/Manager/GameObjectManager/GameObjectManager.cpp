#include "GameObjectManager.h"

#include <stdexcept>

#include "../../Base/GameObject/GameObject.h"
#include "../../Components/Transform/Transform.h"

void GameObjectManager::AddGameObjectDataBase(const SceneType& sceneType)
{
	m_GameObjectList[sceneType] = std::make_shared<GameObjectDataBase>();
}

std::weak_ptr<GameObject> GameObjectManager::AddGameObject(const SceneType& sceneType, const std::string& tag, const std::string& name) {
	return m_GameObjectList[sceneType]->AddGameObject(sceneType, tag, name);
}

std::weak_ptr<GameObject> GameObjectManager::Find(const SceneType& sceneType, const std::string& name)
{
	return m_GameObjectList[sceneType]->Find(name);
}

std::weak_ptr<GameObject> GameObjectManager::FindGameObjectWithTag(const SceneType& sceneType, const std::string& tag)
{
	return m_GameObjectList[sceneType]->FindGameObjectWithTag(tag);
}

std::vector<std::weak_ptr<GameObject>> GameObjectManager::FindGameObjectsWithTag(const SceneType& sceneType, const std::string& tag)
{
	return m_GameObjectList[sceneType]->FindGameObjectsWithTag(tag);
}

void GameObjectManager::RemoveAllGameObject(const SceneType& sceneType)
{
	m_GameObjectList[sceneType]->RemoveAllGameObject();
}

void GameObjectManager::RemoveAllGameObject()
{
	for (const auto& gameObjectList : m_GameObjectList) {
		gameObjectList.second->RemoveAllGameObject();
	}
}
