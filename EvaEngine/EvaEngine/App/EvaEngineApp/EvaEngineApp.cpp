#include "EvaEngineApp.h"
#include "../../Setting/Window/Window.h"
#include "../DirectX11App/DirectX11App.h"
#include "../EditorApp/EditorApp.h"
#include "../../GameSystemBase/DataBase/ModelDataBase/ModelDataBase.h"
#include "../../GameSystemBase/DataBase/ShaderDataBase/ShaderDataBase.h"
#include "../../GameSystemBase/DataBase/TextureDataBase/TextureDataBase.h"
#include "../../GameSystemBase/DataBase/SceneDataBase/SceneDataBase.h"
#include "../../GameSystemBase/Manager/DrawManager/DrawManager.h"

#if _DEBUG
#include "../../Editor/EditorWindowDataBase/EditorWindowDataBase.h"

#include "../../Editor/EditorWindows/ConsoleWindow/ConsoleWindow.h"
#endif

using namespace EvaEngine;

EvaEngineApp::~EvaEngineApp() {
}

HRESULT EvaEngineApp::Init()
{
	HRESULT hr{};

	// 描画マネージャーの初期化
	hr = DrawManager::Init();
	if (FAILED(hr)) {
		DebugLog::LogError("DrawManagerの初期化に失敗しました。");
		return hr;
	}

	// シーンの初期化
	hr = SceneDataBase::Instance().InitializeScene();
	if (FAILED(hr)) {
		DebugLog::LogError("シーンの初期化に失敗しました。");
		return hr;
	}

#if _DEBUG
	// Editorの初期化
	hr = EditorApp::Init();
	if (FAILED(hr)) {
		DebugLog::LogError("Editorの初期化に失敗しました。");
		return hr;
	}

	// EditorWindowの追加
	Internal::EditorWindowDataBase::CreateWindow<Editor::ConsoleWindow>("Console", "Window");
#endif

	return S_OK;
}

void EvaEngineApp::Update()
{
	SceneDataBase::Instance().SceneUpdate();
	SceneDataBase::Instance().FixedUpdate();
	SceneDataBase::Instance().Update();
	SceneDataBase::Instance().LateUpdate();
}

void EvaEngineApp::Draw(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& command)
{
	// 描画開始処理
	DrawManager::DrawBegin();

	// 描画
	SceneDataBase::Instance().Draw(command);

	// 描画終了処理
	DrawManager::DrawEnd();
}

#if _DEBUG
void EvaEngine::EvaEngineApp::DrawEditor()
{
	// Editorの描画開始処理
	EditorApp::DrawBegin();

	EditorCommand editorCommand{};
	// Editorの描画処理
	EditorApp::Draw(&m_SceneView, &editorCommand);
	
	// Editor描画終了処理
	EditorApp::DrawEnd();
}
#endif

void EvaEngineApp::FrameEnd()
{
	SceneDataBase::Instance().SceneChange();
}

void EvaEngine::EvaEngineApp::End()
{
#if _DEBUG
	EditorApp::End();
#endif
}
