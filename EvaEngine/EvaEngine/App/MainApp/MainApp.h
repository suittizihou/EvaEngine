#pragma once

#include <Windows.h>

namespace EvaEngine {
	namespace Internal {
		class MainApp {
		private:
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