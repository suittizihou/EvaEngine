#include "Scene.h"
#include "../../Manager/ComponentManager/ComponentManager.h"

using namespace EvaEngine;
using namespace EvaEngine::Internal;

void EvaEngine::Scene::FixedUpdate() {
    ComponentManager::Instance().FixedUpdate(m_SceneName);
}

void EvaEngine::Scene::Update() {
    ComponentManager::Instance().Update(m_SceneName);
}

void EvaEngine::Scene::LateUpdate() {
    ComponentManager::Instance().LateUpdate(m_SceneName);
}

void EvaEngine::Scene::Draw(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& command)
{
    ComponentManager::Instance().Draw(m_SceneName, command);
}

#if _DEBUG
void EvaEngine::Scene::OnGUI()
{
    ComponentManager::Instance().OnGUI(m_SceneName);
}
#endif

std::weak_ptr<GameObject> Scene::Find(const std::string& name)
{
    return GameObjectManager::Instance().Find(m_SceneName, name);
}

std::weak_ptr<GameObject> Scene::FindGameObjectWithTag(const std::string& tag)
{
    return GameObjectManager::Instance().FindGameObjectWithTag(m_SceneName, tag);
}

std::vector<std::weak_ptr<GameObject>> Scene::FindGameObjectsWithTag(const std::string& tag)
{
    return GameObjectManager::Instance().FindGameObjectsWithTag(m_SceneName, tag);
}

std::string EvaEngine::Scene::GetSceneName() const
{
    return m_SceneName;
}

UINT EvaEngine::Scene::GetSceneID() const
{
    return m_SceneID;
}

std::weak_ptr<GameObject> Scene::Instantiate(const std::string& tag, const std::string& name)
{
    return GameObjectManager::Instance().Instantiate(m_SceneName, tag, name);
}
