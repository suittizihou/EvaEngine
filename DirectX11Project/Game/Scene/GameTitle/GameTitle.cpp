#include "GameTitle.h"
#include "../../Script/CameraScript/CameraScript.h"
#include "../../Script/TestScript/TestScript.h"
#include "../../Script/MoveScript/MoveScript.h"
#include "../../../Utility/Input/Input.h"
#include "../../../GameSystemBase/Manager/SceneManager/SceneManager.h"

GameTitle::GameTitle(const SceneType& sceneType) : Scene(sceneType)
{
}

void GameTitle::Initialize()
{
	AddGameObject("Main Camera").lock()->AddComponent<CameraScript>(Vector3(0.0f, 1.25f, -5.0f), Vector3(0.0f, 0.0f, 0.0f));

	auto charaObj = AddGameObject("Player");
	charaObj.lock()->AddComponent<TestScript>();
	//charaObj.lock()->AddComponent<MoveScript>(0.001f);
}

void GameTitle::SceneUpdate()
{
	if (Input::GetKeyDown(KeyCode::Space)) {
		SceneManager::LoadScene(SceneType::GameMain);
	}
}
