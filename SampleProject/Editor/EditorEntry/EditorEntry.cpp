#include "EditorEntry.h"
#include "../../Scenes/SampleScene/SampleScene.h"
#include "../../Scenes/GameMain/GameMain.h"

using namespace EvaEngine;

void EditorEntry::Init()
{
	SceneManager::AddScene<SampleScene>("SampleScene");
	SceneManager::AddScene<GameMain>("GameMain");
	SceneManager::LoadScene("SampleScene");
}