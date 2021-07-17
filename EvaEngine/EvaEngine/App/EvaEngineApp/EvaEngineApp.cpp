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

	// �`��}�l�[�W���[�̏�����
	hr = DrawManager::Init();
	if (FAILED(hr)) {
		DebugLog::LogError("DrawManager�̏������Ɏ��s���܂����B");
		return hr;
	}

	// �V�[���̏�����
	hr = SceneDataBase::Instance().InitializeScene();
	if (FAILED(hr)) {
		DebugLog::LogError("�V�[���̏������Ɏ��s���܂����B");
		return hr;
	}

#if _DEBUG
	// Editor�̏�����
	hr = EditorApp::Init();
	if (FAILED(hr)) {
		DebugLog::LogError("Editor�̏������Ɏ��s���܂����B");
		return hr;
	}

	// EditorWindow�̒ǉ�
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
	// �`��J�n����
	DrawManager::DrawBegin();

	// �`��
	SceneDataBase::Instance().Draw(command);

	// �`��I������
	DrawManager::DrawEnd();
}

#if _DEBUG
void EvaEngine::EvaEngineApp::DrawEditor()
{
	// Editor�̕`��J�n����
	EditorApp::DrawBegin();

	EditorCommand editorCommand{};
	// Editor�̕`�揈��
	EditorApp::Draw(&m_SceneView, &editorCommand);
	
	// Editor�`��I������
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
