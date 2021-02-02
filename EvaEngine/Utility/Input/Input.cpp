#include "Input.h"
#include "InputBufferUpdate/InputBufferUpdate.h"

bool Input::GetKey(const KeyCode& keyCode)
{
	return InputBufferUpdate::Instance().GetCurrentKeyStatus()[(BYTE)keyCode] == KeyState::Down;
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
	BYTE key = (BYTE)keyCode;
	KeyState state = InputBufferUpdate::Instance().GetCurrentKeyStatus()[key];

	if (state != keyState) return false;

	return InputBufferUpdate::Instance().GetPreviousKeyStatus()[key] != state;
}