#pragma once
#include <Windows.h>

struct D3D11_VIEWPORT;

class Window {
public:
	// DirectX11で使うViewportにして返す
	static D3D11_VIEWPORT GetViewport();

public:
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