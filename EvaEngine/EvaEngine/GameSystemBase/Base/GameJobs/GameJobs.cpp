#include "GameJobs.h"
#include "../../Manager/GameObjectManager/GameObjectManager.h"

using namespace EvaEngine;

std::weak_ptr<GameObject> GameJobs::AddGameObject()
{
    return GameObjectManager::Instance().AddGameObject(m_SceneName, "None", "GameObject");
}

void GameJobs::SetSceneName(const std::string& sceneName)
{
    m_SceneName = sceneName;
}

std::string GameJobs::GetSceneType()
{
    return m_SceneName;
}
