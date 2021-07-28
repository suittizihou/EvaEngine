#include "WindowApp.h"
#include <wrl.h>
#include "../../Setting/Window/Window.h"
#include "../../Utility/Input/InputBufferUpdate/InputBufferUpdate.h"
#include "../../Utility/Input/Input.h"
#include "../DirectX11App/DirectX11App.h"
#include "../../Utility/ModelUtility/ModelData/ModelData.h"
#include "../../Utility/BufferCreate/BufferCreate.h"
#include "../../GameSystemBase/Manager/DrawManager/DrawManager.h"
#include "../../Utility/ShaderUtility/Shader/Shader.h"
#include "../../GameSystemBase/DataBase/ShaderDataBase/ShaderDataBase.h"
#include "../../GameSystemBase/DataBase/ModelDataBase/ModelDataBase.h"
#include "../../Utility/Time/TimeBase.h"

#include "../EvaEngineApp/EvaEngineApp.h"

#include <vector>

using namespace EvaEngine::Internal;

LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {

    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wp, lp)) return true;
    
    switch (msg) {
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, msg, wp, lp);
        break;
    }

    return 0;
}

HRESULT WindowApp::Init()
{
    HRESULT hr{};

    // COMライブラリを初期化するもの(COMとはコンポーネント・オブジェクト・モデルの略)
    // COMライブラリを使う時に使うスレッドで少なくとも１回は実行する必要がある。
    // D3D関連の色んなクラスがこのCOMを利用して実装されており、これをする必要がある
    hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);

    if (FAILED(hr)) {
        DebugLog::LogError("COM Initialize Failed.");
        return hr;
    }

    WNDCLASSEX wc {
        sizeof(WNDCLASSEX),
        CS_HREDRAW | CS_VREDRAW,
        WndProc,
        0L,
        0L,
        GetModuleHandle(NULL),
        NULL,
        LoadCursor(NULL, IDC_ARROW),
        NULL,
        NULL,
        Window::g_WindowName.c_str(),
        NULL
    };

    if (!RegisterClassEx(&wc)) {
        DebugLog::LogError("WNDCLASSEX Initialize Failed.");
        return hr;
    }

    Window::g_wc = wc;

    RECT rect = { 0,0, static_cast<LONG>(Window::g_WindowRight), static_cast<LONG>(Window::g_WindowBottom) };

    // ウィンドウを生成
    Window::g_hWnd = CreateWindow(
        Window::g_WindowName.c_str(),
        Window::g_WindowName.c_str(),
        (WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME) | WS_VISIBLE,
        CW_USEDEFAULT,
        0,
        Window::g_WindowRight - Window::g_WindowLeft, 
        Window::g_WindowBottom - Window::g_WindowTop,
        NULL,
        NULL,
        GetModuleHandle(NULL),
        NULL
    );

    if (!Window::g_hWnd) {
        DebugLog::LogError("Window Create Failed.");
        return E_FAIL;
    }

    RECT window_rect{};
    RECT client_rect{};

    GetWindowRect(Window::g_hWnd, &window_rect);
    GetClientRect(Window::g_hWnd, &client_rect);

    int frame_size_x = (window_rect.right - window_rect.left) - (client_rect.right - client_rect.left);
    int frame_size_y = (window_rect.bottom - window_rect.top) - (client_rect.bottom - client_rect.top);

    SetWindowPos(
        Window::g_hWnd, 
        NULL, 
        CW_USEDEFAULT, 
        0, 
        frame_size_x + static_cast<int>(Window::GetViewport().Width), 
        frame_size_y + static_cast<int>(Window::GetViewport().Height), 
        SWP_NOMOVE);

    ShowWindow(Window::g_hWnd, SW_SHOW);
    UpdateWindow(Window::g_hWnd);

    return hr;
}

int WindowApp::Update()
{
    MSG msg{};
    while (msg.message != WM_QUIT) {

        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {

            if (msg.message == WM_QUIT) {
                break;
            }
            else {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else {
            // 入力処理
            InputBufferUpdate::Instance().KeyUpdate();

            // DeltaTimeを更新
            Internal::TimeBase::UpdateDeltaTime();

            // エンジンの更新処理
            EvaEngineApp::Update();

            // エンジンの描画処理
            //EvaEngineApp::Draw(DirectX11App::g_Context);

#if _DEBUG
            // Editor関連の描画
            EvaEngineApp::DrawEditor();
#endif

            // エンジンのフレーム終了時処理
            EvaEngineApp::FrameEnd();
        }
    }

    // エンジンの終了時処理
    EvaEngineApp::End();

    return static_cast<int>(msg.wParam);
}
