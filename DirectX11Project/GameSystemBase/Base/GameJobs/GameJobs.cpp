#include "GameJobs.h"
#include "../../Manager/GameObjectManager/GameObjectManager.h"

std::weak_ptr<GameObject> GameJobs::AddGameObject()
{
    return GameObjectManager::Instance().AddGameObject(m_SceneType);
}

SceneType GameJobs::GetSceneType()
{
    return m_SceneType;
}
