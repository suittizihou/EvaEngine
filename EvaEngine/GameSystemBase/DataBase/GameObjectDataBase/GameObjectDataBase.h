#pragma once

#include <list>
#include <memory>

#include "../../Base/GameObject/GameObject.h"

class GameObjectDataBase {
public:
	GameObjectDataBase() = default;
	~GameObjectDataBase() = default;

	std::weak_ptr<GameObject> AddGameObject(const SceneType& sceneType, const std::string& tag = "None", const std::string& name = "GameObject");
	// 名前で検索
	std::weak_ptr<GameObject> Find(const std::string& name);
	// タグで検索してゲームオブジェクトを一つ持ってくる
	std::weak_ptr<GameObject> FindGameObjectWithTag(const std::string& tag);
	// タグで検索してヒットしたゲームオブジェクトを全部持ってくる
	std::vector<std::weak_ptr<GameObject>> FindGameObjectsWithTag(const std::string& tag);
	// 保持しているゲームオブジェクトを全削除
	void RemoveAllGameObject();

private:
	UINT m_ObjectID{};
	std::map <std::string,	// Tag 
		std::list<std::shared_ptr<GameObject>>> m_GameObjectList;

};