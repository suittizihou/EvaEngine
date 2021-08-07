#include "EditorApplication.h"
#include "../../GameSystemBase/Manager/SceneManager/SceneManager.h"
#include "../../GameSystemBase/Manager/ComponentManager/ComponentManager.h"

using namespace EvaEngine;
using namespace EvaEngine::Editor;
using namespace EvaEngine::Internal;

bool EditorApplication::isPlaying{ false };
bool EditorApplication::isPause{ false };

bool EditorApplication::sceneWindowIsActive{ false };
bool EditorApplication::gameWindowIsActive{ false };

bool EditorApplication::isInputFreeze{ false };

void EvaEngine::Editor::EditorApplication::Step()
{
	ComponentManager::Instance().FixedUpdate(SceneManager::GetCurrentSceneName());
	ComponentManager::Instance().Update(SceneManager::GetCurrentSceneName());
	ComponentManager::Instance().LateUpdate(SceneManager::GetCurrentSceneName());
}