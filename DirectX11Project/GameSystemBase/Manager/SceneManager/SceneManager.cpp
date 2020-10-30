#include "SceneManager.h"
#include "../../DataBase/SceneDataBase/SceneDataBase.h"

void SceneManager::LoadScene(const SceneType& sceneType)
{
    SceneDataBase::Instance().LoadScene(sceneType);
}

void SceneManager::LoadScene(const UINT& sceneType)
{
    SceneDataBase::Instance().LoadScene(sceneType);
}

SceneType SceneManager::GetCurrentScene()
{
    return SceneDataBase::Instance().GetCurrentSceneType();
}
