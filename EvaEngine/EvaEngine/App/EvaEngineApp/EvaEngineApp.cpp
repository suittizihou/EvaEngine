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

	// �`��}�l�[�W���[�̏�����
	hr = DrawManager::Init();
	if (FAILED(hr)) {
		DebugLog::LogError(u8"DrawManager�̏������Ɏ��s���܂����B");
		return hr;
	}

#if _DEBUG
	// Editor�̏�����
	hr = EditorApp::Init();
	if (FAILED(hr)) {
		DebugLog::LogError(u8"Editor�̏������Ɏ��s���܂����B");
		return hr;
	}
#endif

	// �V�[���̏�����
	hr = SceneDataBase::Instance().SceneChange();
	if (FAILED(hr)) {
		DebugLog::LogError(u8"�V�[���̏������Ɏ��s���܂����B");
		return hr;
	}

	return S_OK;
}

void EvaEngineApp::Update()
{
#if _DEBUG
	if ((EvaEngine::Editor::EditorApplication::isPlaying == false) || EvaEngine::Editor::EditorApplication::isPause) return;
	// �Q�[�����̂̃A�b�v�f�[�g���̓Q�[���E�B���h�E���A�N�e�B�u�o�Ȃ��Ɠ��͂��󂯕t���Ȃ��悤�ɂ���
	EvaEngine::Editor::EditorApplication::isInputFreeze = !EvaEngine::Editor::EditorApplication::gameWindowIsActive;
#endif

	SceneDataBase::Instance().SceneUpdate();
	SceneDataBase::Instance().FixedUpdate();
	SceneDataBase::Instance().Update();
	SceneDataBase::Instance().LateUpdate();

#if _DEBUG
	// �Q�[�����̂̃A�b�v�f�[�g�𔲂�������͏�Ԃ�߂�
	EvaEngine::Editor::EditorApplication::isInputFreeze = false;
#endif
}

void EvaEngineApp::Draw(ID3D11DeviceContext* command)
{
	// �`��
	SceneDataBase::Instance().Draw(command);
}

#if _DEBUG
void EvaEngine::Internal::EvaEngineApp::UpdateEditor()
{
	ComponentManager::Instance().Update("Editor");
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

	if (FAILED(SceneDataBase::Instance().SceneChange())) {
		DebugLog::LogError(u8"�V�[���̏������Ɏ��s���܂����B");
	}
}

void EvaEngineApp::End()
{
	GameObjectManager::Instance().RemoveAllGameObject();
	ComponentManager::Instance().RemoveAllComponent();
	ModelManager::Instance().DeleteAllModel();
	ShaderDataBase::Instance().AllDeleteShader();
	SceneDataBase::Instance().AllDeleteScene();
	Camera::AllDeleteCamera();

#if _DEBUG
	EditorApp::End();
#endif
}
