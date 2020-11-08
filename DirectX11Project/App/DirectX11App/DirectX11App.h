#pragma once
#include "../../Define/D3D11Defines.h"
#include "../../System/DebugLog/DebugLog.h"
#include "../../Utility/ModelUtility/ModelData/ConstantBufferData.h"
#include <memory>

class Camera;

class DirectX11App {
public:
	// DirectXの初期化
	static HRESULT Init();
	static int Update();

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
	static SwapChain g_SwapChain;
	static RenderTargetView g_RenderTargetView;
	static DepthStencilView g_DepthStencilView;

	static ConstantBuffer g_ConstantBuffer;
	static My3DLib::ConstantBufferData g_ConstantBufferData;

private:
	static IDXGIAdapter* m_Adapter;
};