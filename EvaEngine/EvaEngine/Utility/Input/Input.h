#pragma once

#include "KeyCode.h"

namespace EvaEngine {

	class Input {
		Input() = default;
		~Input() = default;
	public:

		// �L�[��������Ă��邩
		static bool GetKey(const KeyCode& keyCode);
		// �L�[���������u��
		static bool GetKeyDown(const KeyCode& keyCode);
		// �L�[�𗣂����u��
		static bool GetKeyUp(const KeyCode& keyCode);
		// �L�[�������ꂽ�u�Ԃ������ꂽ�u�Ԃ�
		static bool GetKeyDownOrUpCheck(const KeyCode& keyCode, const KeyState& keyState);
	};
}