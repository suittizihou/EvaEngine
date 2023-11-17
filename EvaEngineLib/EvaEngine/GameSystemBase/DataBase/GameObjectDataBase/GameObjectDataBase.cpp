#include "GameObjectDataBase.h"

#include <stdexcept>

#include "../../Base/GameObject/GameObject.h"
#include "../../Components/Transform/Transform.h"

using namespace EvaEngine;

std::weak_ptr<GameObject> GameObjectDataBase::AddGameObject(const std::string& sceneType, const std::string& tag, const std::string& name) {
	std::shared_ptr<GameObject> obj = std::make_shared<GameObject>(sceneType, m_ObjectID, tag, name);
	obj->Initialize();
	m_GameObjectList[tag].push_back(obj);
	m_ObjectID += 1;
	return obj;
}

std::weak_ptr<GameObject> GameObjectDataBase::Find(const std::string& name)
{
	for (const auto& objects : m_GameObjectList) {
		for (const auto& obj : objects.second) {
			if (obj->GetName() == name) {
				return obj;
			}
		}
	}

	throw std::runtime_error("Not found : " + name + "という名前のGameObjectは存在しませんでした。");
}

std::weak_ptr<GameObject> GameObjectDataBase::FindGameObjectWithTag(const std::string& tag)
{
	if (m_GameObjectList.count(tag) == 0) {
		throw std::runtime_error("Not found : " + tag + "というTagを持つGameObjectは存在しませんでした。");
		return std::weak_ptr<GameObject>();
	}
	return *m_GameObjectList[tag].begin();
}

std::vector<std::weak_ptr<GameObject>> GameObjectDataBase::FindGameObjectsWithTag(const std::string& tag)
{
	if (m_GameObjectList.count(tag) == 0) {
		throw std::runtime_error("Not found : " + tag + "というTagを持つGameObjectは存在しませんでした。");
		std::vector<std::weak_ptr<GameObject>> nullVector;
		return nullVector;
	}

	std::vector<std::weak_ptr<GameObject>> objVector{ m_GameObjectList[tag].begin(), m_GameObjectList[tag].end() };
	return objVector;
}

void GameObjectDataBase::RemoveAllGameObject()
{
	m_GameObjectList.clear();
	m_ObjectID = 0;
}
