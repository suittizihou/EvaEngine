#pragma once

#include <list>
#include <memory>

#include "../../DataBase/GameObjectDataBase/GameObjectDataBase.h"

namespace EvaEngine {
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
		void AddGameObjectDataBase(const std::string& sceneName);

		std::weak_ptr<GameObject> AddGameObject(const std::string& sceneName, const std::string& tag, const std::string& name);
		// 名前で検索
		std::weak_ptr<GameObject> Find(const std::string& sceneName, const std::string& name);
		// タグで検索してゲームオブジェクトを一つ持ってくる
		std::weak_ptr<GameObject> FindGameObjectWithTag(const std::string& sceneName, const std::string& tag);
		// タグで検索してヒットしたゲームオブジェクトを全部持ってくる
		std::vector<std::weak_ptr<GameObject>> FindGameObjectsWithTag(const std::string& sceneName, const std::string& tag);
		// 保持しているゲームオブジェクトを全削除
		void RemoveAllGameObject(const std::string& sceneName);
		// 保持しているゲームオブジェクトを全削除
		void RemoveAllGameObject();

	private:
		UINT m_ObjectID{};
		std::map <std::string,	// Tag 
			std::shared_ptr<GameObjectDataBase>> m_GameObjectList;
	};
}