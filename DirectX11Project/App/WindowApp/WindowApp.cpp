#include "WindowApp.h"
#include <Windows.h>
#include <wrl.h>
#include "../../Setting/Window/Window.h"
#include "../../System/DebugLog/DebugLog.h"
#include "../../Utility/Input/InputBufferUpdate/InputBufferUpdate.h"
#include "../../Utility/Input/Input.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    PAINTSTRUCT ps;
    HDC hdc;
    switch (msg)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, msg, wp, lp);
}

bool WindowApp::Init()
{
    HRESULT hr{};

    // COMライブラリを初期化するもの(COMとはコンポーネント・オブジェクト・モデルの略)
    // COMライブラリを使う時に使うスレッドで少なくとも１回は実行する必要がある。
    // D3D関連の色んなクラスがこのCOMを利用して実装されており、これをする必要がある(たぶん)
    hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);

    if (FAILED(hr)) {
        DebugLog::LogError("COM Initialize Failed.");
        return false;
    }

    WNDCLASSEX wc{};
    wc.cbSize = sizeof(wc);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = Window::hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.lpszClassName = L"HelloDirectX12";
    RegisterClassEx(&wc);

    DWORD dwStyle = WS_OVERLAPPEDWINDOW & ~WS_SIZEBOX;
    RECT rect = { 0,0, Window::WindowWidthSize, Window::WindowHeightSize };
    AdjustWindowRect(&rect, dwStyle, FALSE);

    // ウィンドウを生成
    Window::hWnd = CreateWindow(wc.lpszClassName, L"DirectX11App",
        dwStyle,
        CW_USEDEFAULT, CW_USEDEFAULT,
        rect.right - rect.left, rect.bottom - rect.top,
        nullptr,
        nullptr,
        wc.hInstance,
        nullptr
    );

    ShowWindow(Window::hWnd, Window::nCmdShow);

    return true;
}

int WindowApp::Update()
{
    UpdateWindow(Window::hWnd);
    MSG msg{};
    while (msg.message != WM_QUIT) {

        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);

            InputBufferUpdate::Instance().KeyUpdate();
        }
    }
    return static_cast<int>(msg.wParam);
}
