#include "Scene.h"

using namespace EvaEngine;

std::weak_ptr<GameObject> Scene::Find(const std::string& name)
{
    return GameObjectManager::Instance().Find(m_SceneName, name);
}

std::weak_ptr<GameObject> Scene::FindGameObjectWithTag(const std::string& tag)
{
    return GameObjectManager::Instance().FindGameObjectWithTag(m_SceneName, tag);
}

std::vector<std::weak_ptr<GameObject>> Scene::FindGameObjectsWithTag(const std::string& tag)
{
    return GameObjectManager::Instance().FindGameObjectsWithTag(m_SceneName, tag);
}

std::string EvaEngine::Scene::GetSceneName() const
{
    return m_SceneName;
}

UINT EvaEngine::Scene::GetSceneID() const
{
    return m_SceneID;
}

std::weak_ptr<GameObject> Scene::AddGameObject(const std::string& tag, const std::string& name)
{
    return GameObjectManager::Instance().AddGameObject(m_SceneName, tag, name);
}
