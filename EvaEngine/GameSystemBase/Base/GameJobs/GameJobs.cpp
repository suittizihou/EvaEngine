#include "GameJobs.h"
#include "../../Manager/GameObjectManager/GameObjectManager.h"

std::weak_ptr<GameObject> GameJobs::AddGameObject()
{
    return GameObjectManager::Instance().AddGameObject(m_SceneType, "None", "GameObject");
}

void GameJobs::SetSceneType(const SceneType& sceneType)
{
    m_SceneType = sceneType;
}

SceneType GameJobs::GetSceneType()
{
    return m_SceneType;
}
