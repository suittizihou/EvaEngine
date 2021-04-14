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

		// 初期化処理
		HRESULT Init();

		// 更新処理
		void Update();
		// 描画処理
		void Draw(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& command);
		// フレーム終了時処理
		void FrameEnd();

		// エンジンの終了時処理
		void End();

	//private:
	//	void InternalInit();
	//	void InternalUpdate();
	//	void InternalDraw(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& command);
	//	void InternalLast();
	};
}