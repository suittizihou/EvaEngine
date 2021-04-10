#include "SampleScene.h"

using namespace EvaEngine;

SampleScene::SampleScene(const std::string sceneName, const UINT sceneID) :
	Scene(sceneName, sceneID)
{
}

void SampleScene::Initialize()
{
	AddGameObject("Main Camera", "Main Camera").lock()->AddComponent<Camera>();
}

void SampleScene::SceneUpdate()
{
}