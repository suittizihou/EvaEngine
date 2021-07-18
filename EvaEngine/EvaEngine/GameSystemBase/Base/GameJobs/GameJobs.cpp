#include "GameJobs.h"
#include "../../Manager/GameObjectManager/GameObjectManager.h"

using namespace EvaEngine;

std::weak_ptr<GameObject> GameJobs::Instantiate(const std::string& tag, const std::string& name)
{
    return EvaEngine::Internal::GameObjectManager::Instance().Instantiate(m_SceneName, tag, name);
}

void GameJobs::SetSceneName(const std::string& sceneName)
{
    m_SceneName = sceneName;
}

std::string GameJobs::GetSceneType()
{
    return m_SceneName;
}
