#pragma once

#include <list>
#include <memory>

#include "../../Base/Scene/SceneType.h"
#include "../../DataBase/GameObjectDataBase/GameObjectDataBase.h"

class GameObject;

class GameObjectManager {
private:
	GameObjectManager() = default;
	~GameObjectManager() = default;

	GameObjectManager(const GameObjectManager&);
	GameObjectManager& operator=(const GameObjectManager&);

public:
	static GameObjectManager& Instance() {
		static GameObjectManager gameObjectManager;
		return gameObjectManager;
	}

	// ゲームオブジェクトデータベースをシーンに追加
	void AddGameObjectDataBase(const SceneType& sceneType);

	std::weak_ptr<GameObject> AddGameObject(const SceneType& sceneType, const std::string& tag, const std::string& name);
	// 名前で検索
	std::weak_ptr<GameObject> Find(const SceneType& sceneType, const std::string& name);
	// タグで検索してゲームオブジェクトを一つ持ってくる
	std::weak_ptr<GameObject> FindGameObjectWithTag(const SceneType& sceneType, const std::string& tag);
	// タグで検索してヒットしたゲームオブジェクトを全部持ってくる
	std::vector<std::weak_ptr<GameObject>> FindGameObjectsWithTag(const SceneType& sceneType, const std::string& tag);
	// 保持しているゲームオブジェクトを全削除
	void RemoveAllGameObject(const SceneType& sceneType);
	// 保持しているゲームオブジェクトを全削除
	void RemoveAllGameObject();

private:
	UINT m_ObjectID{};
	std::map <SceneType,	// Tag 
		std::shared_ptr<GameObjectDataBase>> m_GameObjectList;
};