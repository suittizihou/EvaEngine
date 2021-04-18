#include "EvaEngineApp.h"
#include "../../Setting/Window/Window.h"
#include "../DirectX11App/DirectX11App.h"
#include "../EditorApp/EditorApp.h"
#include "../../GameSystemBase/DataBase/ModelDataBase/ModelDataBase.h"
#include "../../GameSystemBase/DataBase/ShaderDataBase/ShaderDataBase.h"
#include "../../GameSystemBase/DataBase/TextureDataBase/TextureDataBase.h"
#include "../../GameSystemBase/DataBase/SceneDataBase/SceneDataBase.h"
#include "../../GameSystemBase/Manager/DrawManager/DrawManager.h"

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

#if _DEBUG
	// Editorの描画開始処理
	EditorApp::DrawBegin();
#endif

	// 描画
	SceneDataBase::Instance().Draw(command);

#if _DEBUG
	// Editorの描画処理
	EditorApp::Draw(command);
	// Editor描画終了処理
	EditorApp::DrawEnd();
#endif

	// 描画終了処理
	DrawManager::DrawEnd();
}

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
