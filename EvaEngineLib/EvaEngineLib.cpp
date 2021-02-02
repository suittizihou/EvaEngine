#if _DEBUG
#define _CRTDBG_MAP_ALLOC
#endif

#include "pch.h"
#include "framework.h"

#include <Windows.h>
#include <stdexcept>
#include "Setting/Window/Window.h"
#include "App/WindowApp/WindowApp.h"
#include "System/DebugLog/DebugLog.h"

#if _DEBUG
#define NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
#if _DEBUG
    // メモリリーク検出
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

    Window::g_hInstance = hInstance;
    Window::g_nCmdShow = nCmdShow;

    // ウィンドウの初期化
    if (FAILED(WindowApp::Init())) {
        DebugLog::LogError("Window Initialize Failed.");
        return -1;
    }

    int result = WindowApp::Update();

    // メッセージループ
    return result;
}