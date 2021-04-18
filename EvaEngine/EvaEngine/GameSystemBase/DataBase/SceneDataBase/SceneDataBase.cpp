#include "SceneDataBase.h"
#include "../../Manager/ComponentManager/ComponentManager.h"
#include "../../Manager/GameObjectManager/GameObjectManager.h"

using namespace EvaEngine;

void SceneDataBase::LoadScene(const std::string& sceneType)
{
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

std::string SceneDataBase::GetCurrentSceneType()
{
    return m_CurrentSceneName;
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
    // 前のシーンと今のシーンが同じなら早期リターン
    if (m_CurrentSceneName == m_PreviousSceneName) return;

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
void EvaEngine::SceneDataBase::OnGUI(const SceneView& sceneView)
{
    m_CurrentScene.lock()->OnGUI(sceneView);
}
#endif
