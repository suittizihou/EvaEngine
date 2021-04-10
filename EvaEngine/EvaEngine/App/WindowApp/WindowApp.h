#pragma once
#include <Windows.h>

namespace EvaEngine {
	class WindowApp {
	public:
		static HRESULT Init();
		static int Update();
	};
}