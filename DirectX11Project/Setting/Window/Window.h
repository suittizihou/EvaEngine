#pragma once
#include <Windows.h>

class Window {
public:
	// ウィンドウの横幅
	static long WindowWidthSize;
	// ウィンドウの縦幅
	static long WindowHeightSize;
	// インスタンスハンドル(アプリケーション自体を示す値)
	static HINSTANCE hInstance;
	// ウィンドウハンドル(ウィンドウ自体を示す値)
	static HWND hWnd;
	// ウインドウをどのように表示するかを示す定数
	static int nCmdShow;
};