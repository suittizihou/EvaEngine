#include "InputBufferUpdate.h"
#include <stdexcept>

using namespace EvaEngine;

InputBufferUpdate::InputBufferUpdate()
{
	// IDirectInput8インターフェイスの取得
	HRESULT hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInputInterface, nullptr);

	if (FAILED(hr)) {
		throw std::runtime_error("IDirectInput8インターフェイスの取得に失敗");
	}

	// IDirectInputDevice8インターフェイスの取得
	hr = m_pInputInterface->CreateDevice(GUID_SysKeyboard, &m_pKeyDevice, nullptr);
	if (FAILED(hr)) {
		throw std::runtime_error("IDirectInputDevice8インターフェイスの取得に失敗");
	}

	// デバイスのフォーマットの設定
	hr = m_pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr)) {
		throw std::runtime_error("デバイスのフォーマットの設定に失敗");
	}

	// 協調モードの設定
	hr = m_pKeyDevice->SetCooperativeLevel(GetActiveWindow(), DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr)) {
		throw std::runtime_error("協調モードの設定に失敗");
	}

	// デバイスの取得開始
	m_pKeyDevice->Acquire();
}

InputBufferUpdate::~InputBufferUpdate()
{
	m_pKeyDevice->Unacquire();
	m_pKeyDevice->Release();
	m_pKeyDevice = nullptr;
	m_pInputInterface->Release();
	m_pInputInterface = nullptr;
}


void InputBufferUpdate::KeyUpdate()
{
	HRESULT hr;
	// キーボードデバイスのゲッター
	hr = m_pKeyDevice->GetDeviceState(INPUT_BUFFER_SIZE, &m_Keys);

	if (SUCCEEDED(hr)) {

		// 前フレームの入力状態をコピー
		m_PreviousKeyStatus = m_CurrentKeyStatus;

		// 入力されているボタンはDownステートに、そうじゃないボタンはUpステートに
		for (int index = 0; index < INPUT_BUFFER_SIZE; ++index) {
			if (m_Keys[index] & 0x80)
			{
				m_CurrentKeyStatus[index] = KeyState::Down;
			}
			else { m_CurrentKeyStatus[index] = KeyState::Up; }
		}
	}
	else if (hr == DIERR_INPUTLOST) {
		m_pKeyDevice->Acquire();
	}
}

std::array<KeyState, INPUT_BUFFER_SIZE> InputBufferUpdate::GetCurrentKeyStatus()
{
	return m_CurrentKeyStatus;
}

std::array<KeyState, INPUT_BUFFER_SIZE> InputBufferUpdate::GetPreviousKeyStatus()
{
	return m_PreviousKeyStatus;
}
