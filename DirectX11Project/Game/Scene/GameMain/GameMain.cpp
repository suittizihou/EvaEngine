#include "GameMain.h"
#include "../../../Utility/Input/Input.h"
#include "../../../GameSystemBase/Manager/SceneManager/SceneManager.h"
#include "../../Script/TestScript/TestScript.h"
#include "../../Script/CameraScript/CameraScript.h"

GameMain::GameMain(const SceneType& sceneType) : Scene(sceneType)
{
}

void GameMain::Initialize()
{
	AddGameObject("Main Camera").lock()->AddComponent<CameraScript>(Vector3::zero(), Vector3::zero());

	auto chara = AddGameObject();
	chara.lock()->AddComponent<TestScript>();
}

void GameMain::SceneUpdate()
{
	if (Input::GetKeyDown(KeyCode::Space)) {
		SceneManager::LoadScene(SceneType::GameTitle);
	}
}
