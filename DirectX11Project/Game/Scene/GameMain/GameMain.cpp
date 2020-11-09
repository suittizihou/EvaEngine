#include "GameMain.h"
#include "../../../Utility/Input/Input.h"
#include "../../../GameSystemBase/Manager/SceneManager/SceneManager.h"

GameMain::GameMain(const SceneType& sceneType) : Scene(sceneType)
{
}

void GameMain::Initialize()
{

}

void GameMain::SceneUpdate()
{
	if (Input::GetKeyDown(KeyCode::Space)) {
		SceneManager::LoadScene(SceneType::GameTitle);
	}
}
