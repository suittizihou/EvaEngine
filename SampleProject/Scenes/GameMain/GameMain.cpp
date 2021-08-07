#include "GameMain.h"

using namespace EvaEngine;

GameMain::GameMain(const std::string& sceneName, const UINT sceneID) :
	Scene(sceneName, sceneID)
{

}

GameMain::~GameMain()
{
}

void GameMain::Initialize()
{
}

void GameMain::SceneUpdate()
{
	if (Input::GetKeyDown(KeyCode::B)) 
		SceneManager::LoadScene(SceneManager::GetPreviousSceneName());
}
