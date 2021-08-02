#include "EvaEngineApp.h"
#include "../EditorApp/EditorApp.h"
#include "../../Setting/Window/Window.h"
#include "../DirectX11App/DirectX11App.h"
#include "../../GameSystemBase/DataBase/ModelDataBase/ModelDataBase.h"
#include "../../GameSystemBase/DataBase/ShaderDataBase/ShaderDataBase.h"
#include "../../GameSystemBase/DataBase/TextureDataBase/TextureDataBase.h"
#include "../../GameSystemBase/DataBase/SceneDataBase/SceneDataBase.h"
#include "../../GameSystemBase/Manager/DrawManager/DrawManager.h"

#if _DEBUG
using namespace EvaEngine::Editor::Internal;
#endif

using namespace EvaEngine::Internal;

HRESULT EvaEngineApp::Init()
{
	HRESULT hr{};

	// �`��}�l�[�W���[�̏�����
	hr = DrawManager::Init();
	if (FAILED(hr)) {
		DebugLog::LogError("DrawManager�̏������Ɏ��s���܂����B");
		return hr;
	}

#if _DEBUG
	// Editor�̏�����
	hr = EditorApp::Init();
	if (FAILED(hr)) {
		DebugLog::LogError("Editor�̏������Ɏ��s���܂����B");
		return hr;
	}
#endif

	// �V�[���̏�����
	hr = SceneDataBase::Instance().InitializeScene();
	if (FAILED(hr)) {
		DebugLog::LogError("�V�[���̏������Ɏ��s���܂����B");
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

void EvaEngineApp::Draw(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& command)
{
	// �`��
	SceneDataBase::Instance().Draw(command);
}

#if _DEBUG
void EvaEngine::Internal::EvaEngineApp::UpdateEditor()
{
	EditorApp::Update();
}

void EvaEngineApp::DrawEditor()
{
	// Editor�̕`��J�n����
	EditorApp::DrawBegin();

	// Editor�̕`�揈��
	EditorApp::Draw();
	
	// Editor�`��I������
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
#if _DEBUG
	EditorApp::End();
#endif
}
