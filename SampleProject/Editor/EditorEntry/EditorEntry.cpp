#include "EditorEntry.h"
#include "../../Scenes/SampleScene/SampleScene.h"
#include "../../Scenes/GameMain/GameMain.h"

using namespace EvaEngine;

void EditorEntry::Init()
{
	SceneManager::AddScene<SampleScene>(u8"SampleScene");
	SceneManager::AddScene<GameMain>(u8"GameMain");
	SceneManager::LoadScene(u8"SampleScene");
}