#include "ModelManager.h"
#include "../SceneManager/SceneManager.h"
#include "../../DataBase/ModelDataBase/ModelDataBase.h"

using namespace EvaEngine;
using namespace EvaEngine::Internal;

void EvaEngine::ModelManager::AddModelDataBase(const std::string& sceneName)
{
	m_ModelDatas[sceneName] = std::make_shared<ModelDataBase>();
}

int EvaEngine::ModelManager::LoadModel(const std::string& fileName)
{
	return m_ModelDatas[SceneManager::GetCurrentSceneName()]->LoadModelData(fileName);
}

int EvaEngine::ModelManager::LoadModel(const std::shared_ptr<ModelData>& model)
{
	return m_ModelDatas[SceneManager::GetCurrentSceneName()]->LoadModelData(model);
}

std::weak_ptr<ModelData> EvaEngine::ModelManager::GetModel(const int modelHandle)
{
	return m_ModelDatas[SceneManager::GetCurrentSceneName()]->GetModel(modelHandle);
}

void EvaEngine::ModelManager::DeleteModel(const int modelHandle)
{
	m_ModelDatas[SceneManager::GetCurrentSceneName()]->DeleteModel(modelHandle);
}

void EvaEngine::ModelManager::DeleteAllModel()
{
	m_ModelDatas[SceneManager::GetCurrentSceneName()]->DeleteAllModel();
}