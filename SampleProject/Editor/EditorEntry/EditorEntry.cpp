#include "EditorEntry.h"
#include "../../SampleScene/SampleScene.h"

using namespace EvaEngine;

void EditorEntry::Init()
{
	SceneManager::AddScene<SampleScene>("SampleScene");
	SceneManager::LoadScene("SampleScene");
}