#pragma once
#include "../../Define/D3D11Defines.h"
#include "../../System/DebugLog/DebugLog.h"

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
	// レンダーターゲットの作成
	static HRESULT CreateRenderTargetView();
	// 深度ステンシルビューの作成
	static HRESULT CreateDepthAndStencilView();

public:
	static D3DDevice g_Device;
	static D3DContext g_Context;
	static SwapChain g_SwapChain;
	static RenderTargetView g_RenderTargetView;
	static DepthStencilView g_DepthStencilView;

private:
	static IDXGIAdapter* m_Adapter;
};