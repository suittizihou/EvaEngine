#include "GameObjectDataBase.h"

#include <stdexcept>

#include "../../Base/GameObject/GameObject.h"
#include "../../Components/Transform/Transform.h"
#include "../../../Utility/GUIDUtility/GUIDUtility.h"

using namespace EvaEngine;
using namespace EvaEngine::Internal;

std::weak_ptr<GameObject> GameObjectDataBase::Instantiate(const std::u8string& sceneType, const std::string& tag, const std::u8string& name) {
	GUID guid{ GUID_NULL };
	if (GUIDUtility::Create(&guid, u8"GameObjectDataBaseにて " + name + u8" のGUID生成に失敗しました。") == false) return std::weak_ptr<GameObject>();
	std::shared_ptr<GameObject> obj = std::make_shared<GameObject>(sceneType, guid, tag, name);
	obj->Initialize();
	m_GameObjectReference.push_back(obj);
	m_GameObjectListSource[tag].push_back(obj);
	return obj;
}

std::weak_ptr<GameObject> GameObjectDataBase::Find(const std::u8string& name)
{
	for (const auto& objects : m_GameObjectListSource) {
		for (const auto& obj : objects.second) {
			if (obj->GetName() == name) {
				return obj;
			}
		}
	}

	DebugLog::LogError(u8"Not found : " + name + u8"という名前のGameObjectは存在しませんでした。");
}

std::weak_ptr<GameObject> GameObjectDataBase::FindGameObjectWithTag(const std::string& tag)
{
	if (m_GameObjectListSource.count(tag) == 0) {
		DebugLog::LogError(u8"Not found : " + StringAssist::to_u8string(tag) + u8"というTagを持つGameObjectは存在しませんでした。");
		return std::weak_ptr<GameObject>();
	}
	return *m_GameObjectListSource[tag].begin();
}

std::vector<std::weak_ptr<GameObject>> GameObjectDataBase::FindGameObjectsWithTag(const std::string& tag)
{
	if (m_GameObjectListSource.count(tag) == 0) {
		DebugLog::LogError(u8"Not found : " + StringAssist::to_u8string(tag) + u8"というTagを持つGameObjectは存在しませんでした。");
		std::vector<std::weak_ptr<GameObject>> nullVector;
		return nullVector;
	}

	std::vector<std::weak_ptr<GameObject>> objVector{ m_GameObjectListSource[tag].begin(), m_GameObjectListSource[tag].end() };
	return objVector;
}

void EvaEngine::Internal::GameObjectDataBase::GetAllGameObject(std::vector<std::weak_ptr<GameObject>>* outputObjects)
{
	*outputObjects = m_GameObjectReference;
}

void GameObjectDataBase::RemoveAllGameObject()
{
	m_GameObjectListSource.clear();
}
