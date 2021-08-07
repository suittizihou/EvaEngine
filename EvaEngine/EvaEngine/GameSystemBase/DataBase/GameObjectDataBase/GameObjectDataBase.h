#pragma once

#include <list>
#include <memory>

#include "../../Base/GameObject/GameObject.h"

namespace EvaEngine {
	namespace Internal {
		class GameObjectDataBase {
		public:
			GameObjectDataBase() = default;
			~GameObjectDataBase() = default;

			std::weak_ptr<GameObject> Instantiate(const std::string& sceneName, const std::string& tag = "None", const std::string& name = "GameObject");
			// 名前で検索
			std::weak_ptr<GameObject> Find(const std::string& name);
			// タグで検索してゲームオブジェクトを一つ持ってくる
			std::weak_ptr<GameObject> FindGameObjectWithTag(const std::string& tag);
			// タグで検索してヒットしたゲームオブジェクトを全部持ってくる
			std::vector<std::weak_ptr<GameObject>> FindGameObjectsWithTag(const std::string& tag);
			// 所持する全ゲームオブジェクトを返す
			void GetAllGameObject(std::vector<std::weak_ptr<GameObject>>& outputObjects);
			// 保持しているゲームオブジェクトを全削除
			void RemoveAllGameObject();

		private:
			UINT m_ObjectID{};

			// タグで分けず参照を保持するリスト
			std::vector<std::weak_ptr<GameObject>> m_GameObjectReference;
			// ゲームオブジェクトの実体を実際に所有するリスト
			std::map <std::string,	// Tag 
				std::vector<std::shared_ptr<GameObject>>> m_GameObjectListSource;

		};
	}
}