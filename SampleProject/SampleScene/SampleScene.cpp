#include "SampleScene.h"
#include "../Script/Move/Move.h"

using namespace EvaEngine;

SampleScene::SampleScene(const std::string sceneName, const UINT sceneID) :
	Scene(sceneName, sceneID)
{
}

void SampleScene::Initialize()
{
	auto camera = AddGameObject("Main Camera", "Main Camera").lock()->AddComponent<Camera>();
	camera.lock()->GetTransform().lock()->position(Vector3(0.0f, 0.0f, -5.0f));
	camera.lock()->AddGameObject().lock()->AddComponent<Move>(1.0f);

	int modelHandle = ModelLoader::Load("Cylinder.fbx");
	auto mesh = AddGameObject("None", "GameObject").lock()->AddComponent<MeshFilter>(modelHandle);
	mesh.lock()->GetGameObject().lock()->AddComponent<MeshRenderer>(mesh, camera);
	mesh.lock()->GetTransform().lock()->rotate(Vector3(90.0f, 0.0f, 0.0f));
}

void SampleScene::SceneUpdate()
{
}