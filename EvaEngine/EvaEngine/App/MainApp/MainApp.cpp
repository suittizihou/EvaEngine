#include "MainApp.h"
#include "../WindowApp/WindowApp.h"
#include "../DirectX11App/DirectX11App.h"
#include "../EvaEngineApp/EvaEngineApp.h"
#include "../../GameSystemBase/Base/GameBase/GameBase.h"

using namespace EvaEngine::Internal;

HRESULT MainApp::Init()
{
	setlocale(LC_ALL, "jpn");

	// �E�B���h�E�̏�����
	HRESULT hr = WindowApp::Init();
	if (FAILED(hr)) {
		DebugLog::ShowErrorMessageWindow("Window initialize failed.");
		return hr;
	}

	// DirectX11�̏�����
	hr = DirectX11App::Init();
	if (FAILED(hr)) {
		DebugLog::ShowErrorMessageWindow("DirectX initialize failed.");
		return hr;
	}

	// ���[�U�[�̏���������(�V�[���̒ǉ��Ȃǂ����邽�߂����ł���)
	EvaEngine::GameBase::Instance()->Init();

	// �G���W���̏�����
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
#if _DEBUG
	// ���������[�N���o
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif
	
	EvaEngine::Internal::Window::g_hInstance = hInstance;
	EvaEngine::Internal::Window::g_nCmdShow = nCmdShow;

	// EvaEngine�̏�����
	if (FAILED(MainApp::Init())) {
		EvaEngine::DebugLog::ShowErrorMessageWindow("EvaEngine initialize failed.");
		return -1;
	}

	// ���b�Z�[�W���[�v
	int result = MainApp::Run();

	DirectX11App::Release();
#if _DEBUG
	DirectX11App::ReportLiveObjects();
	// �f�o�b�O�Ɏg�����I�u�W�F�N�g�����
	DirectX11App::DebugRelease();
#endif

	return result;
}