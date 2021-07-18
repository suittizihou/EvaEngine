#pragma once

#include <dinput.h>
#include <array>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include "../KeyCode.h"

namespace EvaEngine {
	namespace Internal {
		constexpr unsigned short INPUT_BUFFER_SIZE = (1 << 8);

		class InputBufferUpdate {
		private:
			InputBufferUpdate();
			InputBufferUpdate(const InputBufferUpdate&);
			InputBufferUpdate& operator=(const InputBufferUpdate&);
			~InputBufferUpdate();

		public:
			static InputBufferUpdate& Instance() {
				static InputBufferUpdate instance;
				return instance;
			}

			void KeyUpdate();

			// 最新の入力状態を取得
			std::array<KeyState, INPUT_BUFFER_SIZE> GetCurrentKeyStatus();
			// １フレーム前の入力状態を取得
			std::array<KeyState, INPUT_BUFFER_SIZE> GetPreviousKeyStatus();

		private:
			LPDIRECTINPUT8 m_pInputInterface{};
			LPDIRECTINPUTDEVICE8 m_pKeyDevice{};

			BYTE m_Keys[INPUT_BUFFER_SIZE]{};

			std::array<KeyState, INPUT_BUFFER_SIZE> m_CurrentKeyStatus{}; // 最新の入力状態
			std::array<KeyState, INPUT_BUFFER_SIZE> m_PreviousKeyStatus{}; // 1フレーム前の入力状態
		};
	}
}