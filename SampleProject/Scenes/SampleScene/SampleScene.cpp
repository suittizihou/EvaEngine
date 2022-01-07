#include "SampleScene.h"
#include "../../Script/Move/Move.h"
#include "../../Script/Rotate/Rotate.h"
#include "../../Script/SinMove/SinMove.h"
#include <random>

using namespace EvaEngine;

SampleScene::SampleScene(const std::string& sceneName, const UINT sceneID) :
	Scene(sceneName, sceneID)
{
}

void SampleScene::Initialize()
{
	// ���f���̓ǂݍ���
	GUID modelHandle{ GUID_NULL };
	ModelManager::Instance().LoadModel("TeaPot.fbx", &modelHandle);

	// �Q�[���I�u�W�F�N�g�̐���
	auto gameObject = Instantiate("None", "GameObject");
	// �e�R���|�[�l���g��ǉ�
	gameObject.lock()->AddComponent<MeshFilter>(modelHandle);
	gameObject.lock()->AddComponent<MeshRenderer>();
	gameObject.lock()->AddComponent<SinMove>(2.0f, 1.0f);

	auto cameraParent = Instantiate("None", "CameraParent");
	cameraParent.lock()->GetTransform().lock()->position(Vector3(0.0f, 0.0f, -5.0f));
	cameraParent.lock()->AddComponent<Move>(5.0f);
	cameraParent.lock()->AddComponent<Rotate>(50.0f);

	//std::random_device rand;
	//std::mt19937 mt(rand());
	//std::uniform_real_distribution<> rand_1(2.5f, 5.0f);
	//std::uniform_real_distribution<> rand_2(0.5f, 1.0f);

	//for (int i = 0; i < 1; ++i) {
	//	for (int k = 0; k < 1; ++k) {
	//		auto meshObj = Instantiate("None", "GameObject");
	//		auto mesh = meshObj.lock()->AddComponent<MeshFilter>(0);
	//		mesh.lock()->GetGameObject().lock()->AddComponent<MeshRenderer>(mesh);
	//		mesh.lock()->GetTransform().lock()->rotate(0.0f, 0.0f, 0.0f);
	//		mesh.lock()->GetTransform().lock()->position(i * 2, 0.0f, k * 2);
	//		mesh.lock()->GetGameObject().lock()->AddComponent<SinMove>(2.0f, rand_1(mt));
	//	}
	//}
}

void SampleScene::SceneUpdate()
{
	if (Input::GetKeyDown(KeyCode::B)) {
		SceneManager::LoadScene("GameMain");
	}
}