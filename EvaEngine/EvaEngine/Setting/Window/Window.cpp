#include "Window.h"

using namespace EvaEngine::Internal;

const std::string Window::g_WindowName{ "EvaEngine" };
UINT Window::g_WindowLeft{ 0 };
UINT Window::g_WindowRight{ 1280 };
UINT Window::g_WindowTop{ 0 };
UINT Window::g_WindowBottom{ 720 };
UINT Window::g_FPS{ 144 };
HINSTANCE Window::g_hInstance{};
HWND Window::g_hWnd{};
int Window::g_nCmdShow{};
WNDCLASSEX Window::g_wc{};

D3D11_VIEWPORT Window::GetViewport()
{
	return D3D11_VIEWPORT
	{
		static_cast<FLOAT>(g_WindowLeft),					// ウィンドウの左端の座標
		static_cast<FLOAT>(g_WindowTop),					// ウィンドウの上端の座標
		static_cast<FLOAT>(g_WindowRight - g_WindowLeft),	// ウィンドウの横幅
		static_cast<FLOAT>(g_WindowBottom - g_WindowTop),	// ウィンドウの縦幅
		0.0f,												// 最小深度
		1.0f												// 最大深度
	};
}
