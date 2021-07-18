#include "MonoBehaviour.h"
#include "../../Base/GameObject/GameObject.h"
#include "../Transform/Transform.h"
#include "../../Manager/GameObjectManager/GameObjectManager.h"

using namespace EvaEngine;

MonoBehaviour::MonoBehaviour(
    const UINT& functionMask,
    const bool canMultiAttach,
    const bool canRemove) :
    Component(functionMask, canMultiAttach)
{
}

std::weak_ptr<GameObject> MonoBehaviour::Find(const std::string& name)
{
    return EvaEngine::Internal::GameObjectManager::Instance().Find(GetSceneType(), name);
}

std::weak_ptr<GameObject> MonoBehaviour::FindGameObjectWithTag(const std::string& tag)
{
    return EvaEngine::Internal::GameObjectManager::Instance().FindGameObjectWithTag(GetSceneType(), tag);
}

std::vector<std::weak_ptr<GameObject>> MonoBehaviour::FindGameObjectsWithTag(const std::string& tag)
{
    return EvaEngine::Internal::GameObjectManager::Instance().FindGameObjectsWithTag(GetSceneType(), tag);
}
