#include "SceneDataBase.h"
#include "../../Manager/ComponentManager/ComponentManager.h"
#include "../../Manager/GameObjectManager/GameObjectManager.h"

void SceneDataBase::LoadScene(const SceneType& sceneType)
{
    m_CurrentSceneType = sceneType;    
}

void SceneDataBase::LoadScene(const UINT& sceneType)
{
    m_CurrentSceneType = static_cast<SceneType>(sceneType);
}

SceneType SceneDataBase::GetCurrentSceneType()
{
    return m_CurrentSceneType;
}

void SceneDataBase::InitializeScene() {
    m_CurrentScene = m_Scenes[m_CurrentSceneType];
    Initialize();

    // 今のシーンを保持
    m_PreviousSceneType = m_CurrentSceneType;
}

void SceneDataBase::SceneChange()
{
    // 前のシーンと今のシーンが同じなら早期リターン
    if (m_CurrentSceneType == m_PreviousSceneType) return;

    // 前のシーンで保持していたオブジェクトとコンポーネントを全削除
    ComponentManager::Instance().RemoveAllComponent(m_PreviousSceneType);
    GameObjectManager::Instance().RemoveAllGameObject(m_PreviousSceneType);

    InitializeScene();
}

void SceneDataBase::Initialize()
{
    m_CurrentScene.lock()->Initialize();
}

void SceneDataBase::Update()
{
    m_CurrentScene.lock()->Update();
}

void SceneDataBase::Draw()
{
    m_CurrentScene.lock()->Draw();
}
