#pragma once

#include <d3d11.h>
#include <wrl.h>

namespace EvaEngine {
	class EvaEngineApp {
	private:
		EvaEngineApp() = default;
		EvaEngineApp(const EvaEngineApp&);
		EvaEngineApp& operator=(const EvaEngineApp&);
		~EvaEngineApp();

	public:
		static EvaEngineApp& Instance() {
			static EvaEngineApp instance;
			return instance;
		}

		HRESULT Init();
		void Update();
		void Draw(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& command);
		void Last();

	private:
		void InternalInit();
		void InternalUpdate();
		void InternalDraw(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& command);
		void InternalLast();
	};
}