#include "EvaEngineApp.h"
#include "../EditorApp/EditorApp.h"
#include "../../Setting/Window/Window.h"
#include "../DirectX11App/DirectX11App.h"
#include "../../GameSystemBase/DataBase/ModelDataBase/ModelDataBase.h"
#include "../../GameSystemBase/DataBase/ShaderDataBase/ShaderDataBase.h"
#include "../../GameSystemBase/DataBase/TextureDataBase/TextureDataBase.h"
#include "../../GameSystemBase/DataBase/SceneDataBase/SceneDataBase.h"
#include "../../GameSystemBase/Manager/GameObjectManager/GameObjectManager.h"
#include "../../GameSystemBase/Manager/ComponentManager/ComponentManager.h"
#include "../../GameSystemBase/Components/Camera/Camera.h"
#include "../../GameSystemBase/Manager/DrawManager/DrawManager.h"

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
		DebugLog::LogError("DrawManagerの初期化に失敗しました。");
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

	// シーンの初期化
	hr = SceneDataBase::Instance().InitializeScene();
	if (FAILED(hr)) {
		DebugLog::LogError("シーンの初期化に失敗しました。");
		return hr;
	}

	return S_OK;
}

void EvaEngineApp::Update()
{
	SceneDataBase::Instance().SceneUpdate();
	SceneDataBase::Instance().FixedUpdate();
	SceneDataBase::Instance().Update();
	SceneDataBase::Instance().LateUpdate();
}

void EvaEngineApp::Draw(ID3D11DeviceContext* command)
{
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
	SceneDataBase::Instance().SceneChange();
}

void EvaEngineApp::End()
{
	GameObjectManager::Instance().RemoveAllGameObject();
	ComponentManager::Instance().RemoveAllComponent();
	ModelDataBase::Instance().AllDeleteModel();
	ShaderDataBase::Instance().AllDeleteShader();
	SceneDataBase::Instance().AllDeleteScene();
	Camera::AllDeleteCamera();

#if _DEBUG
	EditorApp::End();
#endif
}
