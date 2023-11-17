#include "GameObject.h"
#include "../../Components/Transform/Transform.h"
#include "../../Manager/GameObjectManager/GameObjectManager.h"

using namespace EvaEngine;

void GameObject::Initialize()
{
    m_Transform = AddComponent<Transform>();
}

const GUID& GameObject::GetObjectID() const
{
    return m_GUID;
}

std::string GameObject::GetName() const
{
    return m_Name;
}

std::string GameObject::GetTag() const
{
    return m_Tag;
}

std::weak_ptr<Transform> GameObject::GetTransform()
{
    return m_Transform;
}

std::weak_ptr<GameObject> GameObject::Find(const std::string& name)
{
    return EvaEngine::Internal::GameObjectManager::Instance().Find(GetSceneName(), name);
}

std::weak_ptr<GameObject> GameObject::FindGameObjectWithTag(const std::string& tag)
{
    return EvaEngine::Internal::GameObjectManager::Instance().FindGameObjectWithTag(GetSceneName(), tag);
}

std::vector<std::weak_ptr<GameObject>> GameObject::FindGameObjectsWithTag(const std::string& tag)
{
    return EvaEngine::Internal::GameObjectManager::Instance().FindGameObjectsWithTag(GetSceneName(), tag);
}

void EvaEngine::GameObject::SetActive(const bool active)
{
    m_IsActive = active;
}

bool EvaEngine::GameObject::ActiveSelf() const
{
    return m_IsActive;
}
