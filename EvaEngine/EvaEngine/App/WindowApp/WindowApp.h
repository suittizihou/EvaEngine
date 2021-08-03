#pragma once
#include <Windows.h>

namespace EvaEngine {
	namespace Internal {
		class WindowApp {
			WindowApp() = default;
			~WindowApp() = default;
		public:
			static HRESULT Init();
			static int Update();
		};
	}
}