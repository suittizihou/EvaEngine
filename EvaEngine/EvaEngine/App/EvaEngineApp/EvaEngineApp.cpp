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
		DebugLog::ShowErrorMessageWindow("DrawManager�̏������Ɏ��s���܂����B");
		return hr;
	}

#if _DEBUG
	// Editor�̏�����
	hr = EditorApp::Init();
	if (FAILED(hr)) {
		DebugLog::ShowErrorMessageWindow("Editor�̏������Ɏ��s���܂����B");
		return hr;
	}
#endif

	// �V�[���̏�����
	hr = SceneDataBase::Instance().SceneChange();
	if (FAILED(hr)) {
		DebugLog::ShowErrorMessageWindow("�V�[���̏������Ɏ��s���܂����B");
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
		DebugLog::LogError("�V�[���̏������Ɏ��s���܂����B");
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
		// �Q�[�����̂̃A�b�v�f�[�g���̓Q�[���E�B���h�E���A�N�e�B�u�o�Ȃ��Ɠ��͂��󂯕t���Ȃ��悤�ɂ���
		EvaEngine::Editor::EditorApplication::isInputFreeze = !EvaEngine::Editor::EditorApplication::gameWindowIsActive;

		SceneDataBase::Instance().SceneUpdate();
		SceneDataBase::Instance().FixedUpdate();
		SceneDataBase::Instance().Update();
	}

	SceneDataBase::Instance().ExecuteEditUpdate();
	
	if (isPlaying) {
		SceneDataBase::Instance().LateUpdate();

		// �Q�[�����̂̃A�b�v�f�[�g�𔲂�������͏�Ԃ�߂�
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
