#include "SceneManager.h"
#include "../../DataBase/SceneDataBase/SceneDataBase.h"

using namespace EvaEngine;

void SceneManager::LoadScene(const std::string& sceneName)
{
    EvaEngine::Internal::SceneDataBase::Instance().LoadScene(sceneName);
}

void SceneManager::LoadScene(const UINT& sceneID)
{
    EvaEngine::Internal::SceneDataBase::Instance().LoadScene(sceneID);
}

std::string SceneManager::GetCurrentSceneName()
{
    return EvaEngine::Internal::SceneDataBase::Instance().GetCurrentSceneName();
}

std::string SceneManager::GetPreviousSceneName()
{
    return EvaEngine::Internal::SceneDataBase::Instance().GetPreviousSceneName();
}