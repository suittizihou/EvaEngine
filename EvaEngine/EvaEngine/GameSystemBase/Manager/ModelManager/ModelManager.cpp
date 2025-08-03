#include "ModelManager.h"
#include "../SceneManager/SceneManager.h"
#include "../../DataBase/ModelDataBase/ModelDataBase.h"

using namespace EvaEngine;
using namespace EvaEngine::Internal;

void EvaEngine::ModelManager::AddModelDataBase(const std::u8string& sceneName)
{
	m_ModelDatas[sceneName] = std::make_shared<ModelDataBase>();
}

void EvaEngine::ModelManager::LoadModel(const std::u8string& fileName, GUID* guid)
{
	return m_ModelDatas[SceneManager::GetCurrentSceneName()]->LoadModelData(fileName, guid);
}

void EvaEngine::ModelManager::LoadModel(const std::shared_ptr<ModelData>& model, GUID* guid)
{
	return m_ModelDatas[SceneManager::GetCurrentSceneName()]->LoadModelData(model, guid);
}

std::weak_ptr<ModelData> EvaEngine::ModelManager::GetModel(const GUID& guid)
{
	return m_ModelDatas[SceneManager::GetCurrentSceneName()]->GetModel(guid);
}

void EvaEngine::ModelManager::DeleteModel(const GUID& guid)
{
	m_ModelDatas[SceneManager::GetCurrentSceneName()]->DeleteModel(guid);
}

void EvaEngine::ModelManager::DeleteAllModel()
{
	m_ModelDatas[SceneManager::GetCurrentSceneName()]->DeleteAllModel();
}