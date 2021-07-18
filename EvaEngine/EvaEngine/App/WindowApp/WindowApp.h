#pragma once
#include <Windows.h>

namespace EvaEngine {
	namespace Internal {
		class WindowApp {
		public:
			static HRESULT Init();
			static int Update();
		};
	}
}