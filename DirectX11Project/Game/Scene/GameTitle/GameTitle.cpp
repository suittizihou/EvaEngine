#include "GameTitle.h"
#include "../../Script/CameraScript/CameraScript.h"
#include "../../Script/TestScript/TestScript.h"
#include "../../Script/MoveScript/MoveScript.h"
#include "../../Script/SinMove/SinMove.h"
#include "../../../Utility/Input/Input.h"
#include "../../Script/JumpScript/JumpScript.h"
#include "../../../GameSystemBase/Manager/SceneManager/SceneManager.h"
#include "../../../GameSystemBase/Components/ComponentHeaders.h"

GameTitle::GameTitle(const SceneType& sceneType) : Scene(sceneType)
{
}

void GameTitle::Initialize()
{
	auto cameraObject = AddGameObject("Main Camera");
	cameraObject.lock()->AddComponent<CameraScript>(Vector3(0.0f, 1.25f, -5.0f), Vector3(0.0f, 0.0f, 0.0f));
	auto camera = cameraObject.lock()->GetComponent<Camera>();

	auto charaObj = AddGameObject("Player");
	charaObj.lock()->AddComponent<TestScript>();
	//charaObj.lock()->AddComponent<MoveScript>(0.001f);

	for (int i = 0; i < 1; ++i) {
		for (int k = 0; k < 1; ++k) {
			auto obj = AddGameObject();
			obj.lock()->GetTransform().lock()->position(Vector3(i + 1.0f * i, 0.0f, k + 1.0f * k));
			obj.lock()->GetTransform().lock()->local_scale(Vector3(0.5f, 0.5f, 0.5f));
			obj.lock()->AddComponent<SinMove>(0.0025f, 0.0003f);
			obj.lock()->AddComponent<MeshRenderer>(obj.lock()->AddComponent<MeshFilter>(1), camera);
			obj.lock()->AddComponent<JumpScript>();
		}
	}
}

void GameTitle::SceneUpdate()
{
	//if (Input::GetKeyDown(KeyCode::Space)) {
	//	SceneManager::LoadScene(SceneType::GameMain);
	//}
}
