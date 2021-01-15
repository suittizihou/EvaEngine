#include "GameTitle.h"
#include "../../Script/CameraScript/CameraScript.h"
#include "../../Script/TestScript/TestScript.h"
#include "../../Script/MoveScript/MoveScript.h"
#include "../../Script/SinMove/SinMove.h"
#include "../../../Utility/Input/Input.h"
#include "../../Script/JumpScript/JumpScript.h"
#include "../../../GameSystemBase/Manager/SceneManager/SceneManager.h"
#include <random>

GameTitle::GameTitle(const SceneType& sceneType) : Scene(sceneType)
{
}

void GameTitle::Initialize()
{
	auto cameraObject = AddGameObject("Main Camera");
	cameraObject.lock()->AddComponent<CameraScript>(Vector3(0.0f, 1.25f, -5.0f), Vector3(0.0f, 0.0f, 0.0f));
	auto camera = cameraObject.lock()->GetComponent<Camera>();

	//auto charaObj = AddGameObject("Player");
	//charaObj.lock()->AddComponent<TestScript>();
	//charaObj.lock()->AddComponent<MoveScript>(0.001f);

	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution<int> dist(1, 3);

	for (int i = 0; i < 10; ++i) {
		for (int k = 0; k < 10; ++k) {
			auto obj = AddGameObject();
			obj.lock()->GetTransform().lock()->position(Vector3(i + 1.0f * i, 0.0f, k + 1.0f * k));
			obj.lock()->GetTransform().lock()->local_scale(Vector3::one());
			obj.lock()->AddComponent<SinMove>(0.025f * dist(mt), 0.03f);
			obj.lock()->AddComponent<MeshRenderer>(obj.lock()->AddComponent<MeshFilter>(2), camera);
			//obj.lock()->AddComponent<JumpScript>();
		}
	}
}

void GameTitle::SceneUpdate()
{
	if (Input::GetKeyDown(KeyCode::Space)) {
		SceneManager::LoadScene(SceneType::GameMain);
	}
}
