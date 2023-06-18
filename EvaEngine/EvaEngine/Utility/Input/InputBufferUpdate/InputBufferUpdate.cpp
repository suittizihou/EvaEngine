#include "InputBufferUpdate.h"
#include <stdexcept>

using namespace EvaEngine::Internal;

InputBufferUpdate::InputBufferUpdate()
{
	// IDirectInput8�C���^�[�t�F�C�X�̎擾
	HRESULT hr = DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInputInterface, nullptr);

	if (FAILED(hr)) {
		throw std::runtime_error("IDirectInput8�C���^�[�t�F�C�X�̎擾�Ɏ��s");
	}

	// IDirectInputDevice8�C���^�[�t�F�C�X�̎擾
	hr = m_pInputInterface->CreateDevice(GUID_SysKeyboard, &m_pKeyDevice, nullptr);
	if (FAILED(hr)) {
		throw std::runtime_error("IDirectInputDevice8�C���^�[�t�F�C�X�̎擾�Ɏ��s");
	}

	// �f�o�C�X�̃t�H�[�}�b�g�̐ݒ�
	hr = m_pKeyDevice->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr)) {
		throw std::runtime_error("�f�o�C�X�̃t�H�[�}�b�g�̐ݒ�Ɏ��s");
	}

	// �������[�h�̐ݒ�
	hr = m_pKeyDevice->SetCooperativeLevel(GetActiveWindow(), DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr)) {
		throw std::runtime_error("�������[�h�̐ݒ�Ɏ��s");
	}

	// �f�o�C�X�̎擾�J�n
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
	// �L�[�{�[�h�f�o�C�X�̃Q�b�^�[
	hr = m_pKeyDevice->GetDeviceState(INPUT_BUFFER_SIZE, &m_Keys);

	if (SUCCEEDED(hr)) {

		// �O�t���[���̓��͏�Ԃ��R�s�[
		m_PreviousKeyStatus = m_CurrentKeyStatus;

		// ���͂���Ă���{�^����Down�X�e�[�g�ɁA��������Ȃ��{�^����Up�X�e�[�g��
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

std::array<EvaEngine::KeyState, INPUT_BUFFER_SIZE> InputBufferUpdate::GetCurrentKeyStatus()
{
	return m_CurrentKeyStatus;
}

std::array<EvaEngine::KeyState, INPUT_BUFFER_SIZE> InputBufferUpdate::GetPreviousKeyStatus()
{
	return m_PreviousKeyStatus;
}
