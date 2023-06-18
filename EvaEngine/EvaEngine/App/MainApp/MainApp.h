#pragma once

#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#include <Windows.h>

namespace EvaEngine {
	namespace Internal {
		class MainApp {
		private:
			MainApp() = default;
			~MainApp() = default;
		public:

			/// <summary>
			/// �E�B���h�E�ADirectX�A�Q�[���G���W���̏�������S�����
			/// </summary>
			/// <returns></returns>
			static HRESULT Init();

			/// <summary>
			/// ���C�����[�v�ɓ���
			/// </summary>
			/// <returns></returns>
			static int Run();
		};
	}
}