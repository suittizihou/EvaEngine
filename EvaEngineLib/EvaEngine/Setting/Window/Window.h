#pragma once
#include <Windows.h>
#include <string>
#include <d3d11.h>

namespace EvaEngine {

	class Window {
	public:
		// DirectX11で使うViewportにして返す
		static D3D11_VIEWPORT GetViewport();

	public:
		// ウィンドウ名
		static const std::string g_WindowName;
		// ウィンドウの左端
		static UINT g_WindowLeft;
		// ウィンドウの右端
		static UINT g_WindowRight;
		// ウィンドウの上端
		static UINT g_WindowTop;
		// ウィンドウの下端
		static UINT g_WindowBottom;
		// 画面のリフレッシュレート
		static UINT g_FPS;
		// インスタンスハンドル(アプリケーション自体を示す値)
		static HINSTANCE g_hInstance;
		// ウィンドウハンドル(ウィンドウ自体を示す値)
		static HWND g_hWnd;
		// ウインドウをどのように表示するかを示す定数
		static int g_nCmdShow;
	};
}