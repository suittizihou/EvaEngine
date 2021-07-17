#include "SceneManager.h"
#include "../../DataBase/SceneDataBase/SceneDataBase.h"

using namespace EvaEngine;

void SceneManager::LoadScene(const std::string& sceneName)
{
    SceneDataBase::Instance().LoadScene(sceneName);
}

void SceneManager::LoadScene(const UINT& sceneID)
{
    SceneDataBase::Instance().LoadScene(sceneID);
}

std::string SceneManager::GetCurrentSceneName()
{
    return SceneDataBase::Instance().GetCurrentSceneName();
}

std::string SceneManager::GetPreviousSceneName()
{
    return SceneDataBase::Instance().GetPreviousSceneName();
}