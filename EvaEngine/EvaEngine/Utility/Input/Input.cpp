#include "Input.h"
#include "InputBufferUpdate/InputBufferUpdate.h"
#include "../../Editor/EditorApplication/EditorApplication.h"

using namespace EvaEngine;

bool Input::GetKey(const KeyCode& keyCode)
{
#if _DEBUG
	// ���͂��󂯕t���Ȃ��t���O�������Ă��鎞��false
	if (EvaEngine::Editor::EditorApplication::isInputFreeze) return false;
#endif

	return EvaEngine::Internal::InputBufferUpdate::Instance().GetCurrentKeyStatus()[(BYTE)keyCode] == KeyState::Down;
}

bool Input::GetKeyDown(const KeyCode& keyCode)
{
	return GetKeyDownOrUpCheck(keyCode, KeyState::Down);
}

bool Input::GetKeyUp(const KeyCode& keyCode)
{
	return GetKeyDownOrUpCheck(keyCode, KeyState::Up);
}

bool Input::GetKeyDownOrUpCheck(const KeyCode& keyCode, const KeyState& keyState)
{
#if _DEBUG
	// ���͂��󂯕t���Ȃ��t���O�������Ă��鎞��false
	if (EvaEngine::Editor::EditorApplication::isInputFreeze) return false;
#endif

	BYTE key = (BYTE)keyCode;
	KeyState state = EvaEngine::Internal::InputBufferUpdate::Instance().GetCurrentKeyStatus()[key];

	if (state != keyState) return false;

	return EvaEngine::Internal::InputBufferUpdate::Instance().GetPreviousKeyStatus()[key] != state;
}