#include "SampleScene.h"
#include "../Script/Move/Move.h"
#include "../Script/Rotate/Rotate.h"

using namespace EvaEngine;

SampleScene::SampleScene(const std::string sceneName, const UINT sceneID) :
	Scene(sceneName, sceneID)
{
}

void SampleScene::Initialize()
{
	auto cameraParent = Instantiate("None", "CameraParent");
	cameraParent.lock()->GetTransform().lock()->position(Vector3(0.0f, 0.0f, -5.0f));
	cameraParent.lock()->AddComponent<Move>(0.1f);
	cameraParent.lock()->AddComponent<Rotate>(1.0f);

	int modelHandle = ModelLoader::Load("Cylinder.fbx");
	auto mesh = Instantiate("None", "GameObject").lock()->AddComponent<MeshFilter>(modelHandle);
	mesh.lock()->GetGameObject().lock()->AddComponent<MeshRenderer>(mesh);
	mesh.lock()->GetTransform().lock()->rotate(90.0f, 0.0f, 0.0f);
	mesh.lock()->GetTransform().lock()->position(0.0f, 0.0f, 0.0f);
}

void SampleScene::SceneUpdate()
{
}