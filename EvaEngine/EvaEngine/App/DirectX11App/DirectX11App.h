#pragma once
#include "../../Define/D3D11Defines.h"
#include "../../System/DebugLog/DebugLog.h"
#include "../../Utility/ModelUtility/ModelData/ConstantBufferData.h"
#include <memory>
#include <dxgidebug.h>

namespace EvaEngine {
	struct Vector3;
	class Camera;
	
	namespace Internal {

		class DirectX11App {
			DirectX11App() = default;
			~DirectX11App() = default;
		public:

			// DirectXの初期化
			static HRESULT Init();
			// ComPtrたちの解放
			static void Release();

#if _DEBUG
			// ComPtrのメモリリークを出力
			static void ReportLiveObjects();
			// Debugに使ったオブジェクトを解放
			static void DebugRelease();
#endif

		private:
			// ハードウェアのチェック(つよつよGPUを見つけてそのGPUを使うようにする)
			static HRESULT HardWareCheck();
			// デバイスとスワップチェインの作成
			static HRESULT CreateDeviceAndSwapChain();
			// ラスタライザの作成
			static HRESULT CreateRasterizerState();
			// レンダーターゲットの作成
			static HRESULT CreateRenderTargetView();
			// 深度ステンシルビューの作成
			static HRESULT CreateDepthAndStencilView();
			// 定数バッファの作成
			static HRESULT CreateConstantBuffer();
			// 定数バッファのセット
			static void SetConstantBuffer(const std::weak_ptr<Camera>& camera, const Vector3& lightDir, const Vector3& lightColor);

		public:
			static ID3D11Device* g_Device;
			static ID3D11DeviceContext* g_Context;
			static IDXGISwapChain* g_SwapChain;
			static ID3D11RenderTargetView* g_EditorRenderTargetView;
			static ID3D11DepthStencilView* g_EditorDepthStencilView;

			static ID3D11Buffer* g_ConstantBuffer;
			static ConstantBufferData g_ConstantBufferData;

#if _DEBUG
			static IDXGIDebug* g_pDxgiDebug;
			static ID3D11Debug* g_pD3DDebug;
#endif

		private:
			static IDXGIAdapter* m_Adapter;
		};
	}
}