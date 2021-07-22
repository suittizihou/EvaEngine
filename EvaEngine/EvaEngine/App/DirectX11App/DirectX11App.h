#pragma once
#include "../../Define/D3D11Defines.h"
#include "../../System/DebugLog/DebugLog.h"
#include "../../Utility/ModelUtility/ModelData/ConstantBufferData.h"
#include <memory>

namespace EvaEngine {
	class Camera;
	
	namespace Internal {

		class DirectX11App {
		public:
			// DirectXの初期化
			static HRESULT Init();

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
			static void SetConstantBuffer(const std::weak_ptr<Camera>& camera);

		public:
			static D3DDevice g_Device;
			static D3DContext g_Context;
			static D3DSwapChain g_SwapChain;
			static D3DRenderTargetView g_RenderTargetView;
			static D3DDepthStencilView g_DepthStencilView;

			static ConstantBuffer g_ConstantBuffer;
			static ConstantBufferData g_ConstantBufferData;

		private:
			static IDXGIAdapter* m_Adapter;
		};
	}
}