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

	// •`‰æƒ}ƒl[ƒWƒƒ[‚Ì‰Šú‰»
	hr = DrawManager::Init();
	if (FAILED(hr)) {
		DebugLog::LogError("DrawManager‚Ì‰Šú‰»‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
		return hr;
	}

#if _DEBUG
	// Editor‚Ì‰Šú‰»
	hr = EditorApp::Init();
	if (FAILED(hr)) {
		DebugLog::LogError("Editor‚Ì‰Šú‰»‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
		return hr;
	}
#endif

	// ƒV[ƒ“‚Ì‰Šú‰»
	hr = SceneDataBase::Instance().InitializeScene();
	if (FAILED(hr)) {
		DebugLog::LogError("ƒV[ƒ“‚Ì‰Šú‰»‚ÉŽ¸”s‚µ‚Ü‚µ‚½B");
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
	// •`‰æ
	SceneDataBase::Instance().Draw(command);
}

#if _DEBUG
void EvaEngine::Internal::EvaEngineApp::UpdateEditor()
{
	ComponentManager::Instance().Update("Editor");
}

void EvaEngineApp::DrawEditor()
{
	// Editor‚Ì•`‰æŠJŽnˆ—
	EditorApp::DrawBegin();

	// Editor‚Ì•`‰æˆ—
	EditorApp::Draw();
	
	// Editor•`‰æI—¹ˆ—
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
