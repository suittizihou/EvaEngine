#pragma once

#include <list>
#include <memory>

#include "../../DataBase/GameObjectDataBase/GameObjectDataBase.h"

namespace EvaEngine {
	class GameObject;

	namespace Internal {
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
			void AddGameObjectDataBase(const std::u8string& sceneName);

			// 指定したシーンにオブジェクトを生成
			std::weak_ptr<GameObject> Instantiate(const std::u8string& sceneName, const std::string& tag, const std::u8string& name);
			// 名前で検索
			std::weak_ptr<GameObject> Find(const std::u8string& sceneName, const std::u8string& name);
			// タグで検索してゲームオブジェクトを一つ持ってくる
			std::weak_ptr<GameObject> FindGameObjectWithTag(const std::u8string& sceneName, const std::string& tag);
			// タグで検索してヒットしたゲームオブジェクトを全部持ってくる
			std::vector<std::weak_ptr<GameObject>> FindGameObjectsWithTag(const std::u8string& sceneName, const std::string& tag);
			// 指定したシーンのGameObjectDataBaseを取得
			std::weak_ptr<GameObjectDataBase> GetGameObjectDataBase(const std::u8string& sceneName);
			// 保持しているゲームオブジェクトを全削除
			void RemoveAllGameObject(const std::u8string& sceneName);
			// 保持しているゲームオブジェクトを全削除
			void RemoveAllGameObject();

		private:
			UINT m_ObjectID{};
			std::unordered_map <std::u8string,	// SceneName
				std::shared_ptr<GameObjectDataBase>> m_GameObjectList;
		};
	}
}