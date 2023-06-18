#include "SceneDataBase.h"
#include "../../Manager/ComponentManager/ComponentManager.h"
#include "../../Manager/GameObjectManager/GameObjectManager.h"

using namespace EvaEngine::Internal;

void SceneDataBase::LoadScene(const std::string& sceneType)
{
    m_IsChangeScene = true;

    // �O�̃V�[������ێ�
    m_PreviousSceneName = m_CurrentSceneName;
    m_CurrentSceneName = sceneType;
}

void SceneDataBase::LoadScene(const UINT& sceneID)
{
    for (const auto& scene : m_Scenes) {
        if (scene.second->GetSceneID() == sceneID) {
            // �O�̃V�[������ێ�
            m_PreviousSceneName = m_CurrentSceneName;
            m_CurrentSceneName = scene.second->GetSceneName();
            return;
        }
    }
}

std::string SceneDataBase::GetCurrentSceneName() const
{
    return m_CurrentSceneName;
}

std::string SceneDataBase::GetPreviousSceneName() const
{
    return m_PreviousSceneName;
}

HRESULT SceneDataBase::InitializeScene() {
    try {
        // �V�[�����Z�b�g�Z�b�g����ĂȂ�������ŏ��ɒǉ������V�[�������[�h����
        if (m_CurrentSceneName.empty()) m_CurrentSceneName = m_Scenes.begin()->first;

        m_CurrentScene = m_Scenes[m_CurrentSceneName];
        Initialize();

        return S_OK;
    }
    catch (std::string error) {
        return E_ABORT;
    }
}

HRESULT SceneDataBase::SceneChange()
{
    // �V�[���؂�ւ��t���O�������Ă��Ȃ������瑁�����^�[��
    if (!m_IsChangeScene) return S_OK;

    m_IsChangeScene = false;

    if (IsCheckExists(m_CurrentSceneName) == false) {
        DebugLog::LogError(m_CurrentSceneName + u8" �͓o�^����Ă��Ȃ��V�[���ł��B");
        return E_ABORT;
    }

    // �O�̃V�[���ŕێ����Ă����I�u�W�F�N�g�ƃR���|�[�l���g��S�폜
    ComponentManager::Instance().RemoveAllComponent(m_PreviousSceneName);
    GameObjectManager::Instance().RemoveAllGameObject(m_PreviousSceneName);

    return InitializeScene();
}

bool EvaEngine::Internal::SceneDataBase::IsCheckExists(const std::string& sceneName)
{
    return m_Scenes.count(sceneName) == 1;
}

size_t EvaEngine::Internal::SceneDataBase::GetSceneCount() const
{
    return m_Scenes.size();
}

void SceneDataBase::Initialize()
{
    m_CurrentScene.lock()->Initialize();
}

void SceneDataBase::SceneUpdate()
{
    m_CurrentScene.lock()->SceneUpdate();
}

void SceneDataBase::FixedUpdate()
{
    m_CurrentScene.lock()->FixedUpdate();
}

void SceneDataBase::Update()
{
    m_CurrentScene.lock()->Update();
}

void SceneDataBase::ExecuteEditUpdate() {
    m_CurrentScene.lock()->ExecuteEditUpdate();
}

void SceneDataBase::LateUpdate()
{
    m_CurrentScene.lock()->LateUpdate();
}

void SceneDataBase::Draw(ID3D11DeviceContext* command)
{
    m_CurrentScene.lock()->Draw(command);
}

#if _DEBUG
void SceneDataBase::OnGUI()
{
    m_CurrentScene.lock()->OnGUI();
}
#endif

void EvaEngine::Internal::SceneDataBase::AllDeleteScene()
{
    m_Scenes.clear();
}