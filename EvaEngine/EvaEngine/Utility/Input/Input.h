#pragma once

#include "KeyCode.h"

namespace EvaEngine {

	class Input {
		Input() = default;
		~Input() = default;
	public:

		// キーが押されているか
		static bool GetKey(const KeyCode& keyCode);
		// キーを押した瞬間
		static bool GetKeyDown(const KeyCode& keyCode);
		// キーを離した瞬間
		static bool GetKeyUp(const KeyCode& keyCode);
		// キーが押された瞬間か離された瞬間か
		static bool GetKeyDownOrUpCheck(const KeyCode& keyCode, const KeyState& keyState);
	};
}