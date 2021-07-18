#include "SceneDataBase.h"
#include "../../Manager/ComponentManager/ComponentManager.h"
#include "../../Manager/GameObjectManager/GameObjectManager.h"

using namespace EvaEngine::Internal;

void SceneDataBase::LoadScene(const std::string& sceneType)
{
    m_IsChangeScene = true;
    m_CurrentSceneName = sceneType;
}

void SceneDataBase::LoadScene(const UINT& sceneID)
{
    for (const auto& scene : m_Scenes) {
        if (scene.second->GetSceneID() == sceneID) {
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
        // シーンがセットセットされてなかったら最初に追加したシーンをロードする
        if (m_CurrentSceneName.empty()) m_CurrentSceneName = m_Scenes.begin()->first;

        m_CurrentScene = m_Scenes[m_CurrentSceneName];
        Initialize();

        // 今のシーンを保持
        m_PreviousSceneName = m_CurrentSceneName;

        return S_OK;
    }
    catch (std::string error) {
        return E_ABORT;
    }
}

void SceneDataBase::SceneChange()
{
    // シーン切り替わりフラグが立っていなかったら早期リターン
    if (!m_IsChangeScene) return;

    m_IsChangeScene = false;

    // 前のシーンで保持していたオブジェクトとコンポーネントを全削除
    ComponentManager::Instance().RemoveAllComponent(m_PreviousSceneName);
    GameObjectManager::Instance().RemoveAllGameObject(m_PreviousSceneName);

    InitializeScene();
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

void SceneDataBase::LateUpdate()
{
    m_CurrentScene.lock()->LateUpdate();
}

void SceneDataBase::Draw(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& command)
{
    m_CurrentScene.lock()->Draw(command);
}

#if _DEBUG
void SceneDataBase::OnGUI()
{
    m_CurrentScene.lock()->OnGUI();
}
#endif
