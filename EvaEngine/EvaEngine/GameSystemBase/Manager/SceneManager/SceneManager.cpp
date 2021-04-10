#include "SceneManager.h"
#include "../../DataBase/SceneDataBase/SceneDataBase.h"

using namespace EvaEngine;

void SceneManager::LoadScene(const std::string& sceneName)
{
    SceneDataBase::Instance().LoadScene(sceneName);
}

void SceneManager::LoadScene(const UINT& sceneName)
{
    SceneDataBase::Instance().LoadScene(sceneName);
}

std::string SceneManager::GetCurrentScene()
{
    return SceneDataBase::Instance().GetCurrentSceneType();
}
