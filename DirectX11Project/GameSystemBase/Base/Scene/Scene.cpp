#include "Scene.h"

std::weak_ptr<GameObject> Scene::AddGameObject(const std::string& name, const std::string& tag)
{
    return GameObjectManager::Instance().AddGameObject(m_SceneType, name, tag);
}
