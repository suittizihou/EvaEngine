#include "Scene.h"

std::weak_ptr<GameObject> Scene::Find(const std::string& name)
{
    return GameObjectManager::Instance().Find(m_SceneType, name);
}

std::weak_ptr<GameObject> Scene::FindGameObjectWithTag(const std::string& tag)
{
    return GameObjectManager::Instance().FindGameObjectWithTag(m_SceneType, tag);
}

std::vector<std::weak_ptr<GameObject>> Scene::FindGameObjectsWithTag(const std::string& tag)
{
    return GameObjectManager::Instance().FindGameObjectsWithTag(m_SceneType, tag);
}


std::weak_ptr<GameObject> Scene::AddGameObject(const std::string& name, const std::string& tag)
{
    return GameObjectManager::Instance().AddGameObject(m_SceneType, name, tag);
}
