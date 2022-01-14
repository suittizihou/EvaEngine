#include "EvaEngineApp.h"
#include "../EditorApp/EditorApp.h"
#include "../../Setting/Window/Window.h"
#include "../DirectX11App/DirectX11App.h"
#include "../../GameSystemBase/DataBase/ShaderDataBase/ShaderDataBase.h"
#include "../../GameSystemBase/DataBase/TextureDataBase/TextureDataBase.h"
#include "../../GameSystemBase/DataBase/SceneDataBase/SceneDataBase.h"
#include "../../GameSystemBase/Manager/GameObjectManager/GameObjectManager.h"
#include "../../GameSystemBase/Manager/ComponentManager/ComponentManager.h"
#include "../../GameSystemBase/Components/Camera/Camera.h"
#include "../../GameSystemBase/Manager/DrawManager/DrawManager.h"
#include "../../GameSystemBase/Manager/ModelManager/ModelManager.h"
#include "../../Editor/EditorApplication/EditorApplication.h"

#if _DEBUG
using namespace EvaEngine::Editor::Internal;
#endif

using namespace EvaEngine::Internal;

HRESULT EvaEngineApp::Init()
{
	HRESULT hr{};

	// 描画マネージャーの初期化
	hr = DrawManager::Init();
	if (FAILED(hr)) {
		DebugLog::ShowErrorMessageWindow("DrawManagerの初期化に失敗しました。");
		return hr;
	}

#if _DEBUG
	// Editorの初期化
	hr = EditorApp::Init();
	if (FAILED(hr)) {
		DebugLog::ShowErrorMessageWindow("Editorの初期化に失敗しました。");
		return hr;
	}
#endif

	// シーンの初期化
	hr = SceneDataBase::Instance().SceneChange();
	if (FAILED(hr)) {
		DebugLog::ShowErrorMessageWindow("シーンの初期化に失敗しました。");
		return hr;
	}

	return S_OK;
}

void EvaEngineApp::Update()
{
	if (SceneDataBase::Instance().GetSceneCount() <= 0) return;
#if _DEBUG
	EditorUpdate();
#else
	RuntimeUpdate();
#endif
}

void EvaEngineApp::Draw(ID3D11DeviceContext* command)
{
	if (SceneDataBase::Instance().GetSceneCount() <= 0) return;
	// 描画
	SceneDataBase::Instance().Draw(command);
}

#if _DEBUG
void EvaEngine::Internal::EvaEngineApp::UpdateEditor()
{
	ComponentManager::Instance().Update("Editor");
}

void EvaEngineApp::DrawEditor()
{
	// Editorの描画開始処理
	EditorApp::DrawBegin();

	// Editorの描画処理
	EditorApp::Draw();
	
	// Editor描画終了処理
	EditorApp::DrawEnd();
}
#endif

void EvaEngineApp::FrameEnd()
{
	DrawManager::DrawEnd();	// SwapChain->Present

	if (FAILED(SceneDataBase::Instance().SceneChange())) {
		DebugLog::LogError("シーンの初期化に失敗しました。");
	}
}

void EvaEngineApp::End()
{
	GameObjectManager::Instance().RemoveAllGameObject();
	ComponentManager::Instance().RemoveAllComponent();
	Camera::AllDeleteCamera();
	ShaderDataBase::Instance().AllDeleteShader();
	
	if (SceneDataBase::Instance().GetSceneCount() >= 1) {
		ModelManager::Instance().DeleteAllModel();
		SceneDataBase::Instance().AllDeleteScene();
	}

#if _DEBUG
	EditorApp::End();
#endif
}

void EvaEngine::Internal::EvaEngineApp::EditorUpdate()
{
	bool isPlaying = EvaEngine::Editor::EditorApplication::isPlaying && (EvaEngine::Editor::EditorApplication::isPause == false);

	if (isPlaying) {
		// ゲーム自体のアップデート中はゲームウィンドウがアクティブ出ないと入力を受け付けないようにする
		EvaEngine::Editor::EditorApplication::isInputFreeze = !EvaEngine::Editor::EditorApplication::gameWindowIsActive;

		SceneDataBase::Instance().SceneUpdate();
		SceneDataBase::Instance().FixedUpdate();
		SceneDataBase::Instance().Update();
	}

	SceneDataBase::Instance().ExecuteEditUpdate();
	
	if (isPlaying) {
		SceneDataBase::Instance().LateUpdate();

		// ゲーム自体のアップデートを抜けたら入力状態を戻す
		EvaEngine::Editor::EditorApplication::isInputFreeze = false;
	}
}

void EvaEngine::Internal::EvaEngineApp::RuntimeUpdate()
{
	SceneDataBase::Instance().SceneUpdate();
	SceneDataBase::Instance().FixedUpdate();
	SceneDataBase::Instance().Update();
	SceneDataBase::Instance().ExecuteEditUpdate();
	SceneDataBase::Instance().LateUpdate();
}
