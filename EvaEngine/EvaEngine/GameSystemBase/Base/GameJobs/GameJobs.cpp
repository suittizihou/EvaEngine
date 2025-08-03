#include "GameJobs.h"
#include "../../Manager/GameObjectManager/GameObjectManager.h"

using namespace EvaEngine;

std::weak_ptr<GameObject> GameJobs::Instantiate(const std::string& tag, const std::u8string& name)
{
    return EvaEngine::Internal::GameObjectManager::Instance().Instantiate(m_SceneName, tag, name);
}

void GameJobs::SetSceneName(const std::u8string& sceneName)
{
    m_SceneName = sceneName;
}

std::u8string GameJobs::GetSceneName()
{
    return m_SceneName;
}
