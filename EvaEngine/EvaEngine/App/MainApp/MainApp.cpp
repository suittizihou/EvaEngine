#include "MainApp.h"
#include "../WindowApp/WindowApp.h"
#include "../DirectX11App/DirectX11App.h"
#include "../EvaEngineApp/EvaEngineApp.h"
#include "../../GameSystemBase/Base/GameBase/GameBase.h"

using namespace EvaEngine::Internal;

HRESULT MainApp::Init()
{
	setlocale(LC_ALL, "jpn");

	// ウィンドウの初期化
	HRESULT hr = WindowApp::Init();
	if (FAILED(hr)) {
		DebugLog::ShowErrorMessageWindow("Window initialize failed.");
		return hr;
	}

	// DirectX11の初期化
	hr = DirectX11App::Init();
	if (FAILED(hr)) {
		DebugLog::ShowErrorMessageWindow("DirectX initialize failed.");
		return hr;
	}

	// ユーザーの初期化処理(シーンの追加などがあるためここでする)
	EvaEngine::GameBase::Instance()->Init();

	// エンジンの初期化
	hr = EvaEngineApp::Init();
	if (FAILED(hr)) {
		DebugLog::ShowErrorMessageWindow("EvaEngine initialize failed.");
		return hr;
	}

	return hr;
}

int MainApp::Run()
{
	return WindowApp::Update();
}

#include "../../Setting/Window/Window.h"
#include <stdexcept>

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
	EvaEngine::Internal::Window::g_hInstance = hInstance;
	EvaEngine::Internal::Window::g_nCmdShow = nCmdShow;

	// EvaEngineの初期化
	if (FAILED(MainApp::Init())) {
		EvaEngine::DebugLog::ShowErrorMessageWindow("EvaEngine initialize failed.");
		return -1;
	}

	// メッセージループ
	int result = MainApp::Run();

	DirectX11App::Release();
#if _DEBUG
	DirectX11App::ReportLiveObjects();
	// デバッグに使ったオブジェクトを解放
	DirectX11App::DebugRelease();
#endif

	return result;
}