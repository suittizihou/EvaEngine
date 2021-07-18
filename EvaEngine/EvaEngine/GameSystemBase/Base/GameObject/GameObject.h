#pragma once

#include "GameObjectBase.h"
#include "../../Manager/ComponentManager/ComponentManager.h"

namespace EvaEngine {

	class Transform;

	class GameObject final : public GameObjectBase {
	public:
		GameObject(
			const std::string& sceneName = "",
			const UINT& gameObjectID = 0,
			const std::string& tag = "",
			const std::string& name = "") :
			GameObjectBase(sceneName),
			m_GameObjectID(gameObjectID),
			m_Tag(tag),
			m_Name(name)
		{};

		~GameObject() = default;

		// 初期化処理
		void Initialize() override;

		// ObjectIDを返す
		UINT GetObjectID() const override;
		// 名前を返す
		std::string GetName() const override;
		// タグを返す
		std::string GetTag() const override;
		// Transformを返す
		std::weak_ptr<Transform> GetTransform();

		// コンポーネントの登録
		template<class T, class... Args>
		std::weak_ptr<T> AddComponent(Args&& ... args) {
			return EvaEngine::Internal::ComponentManager::Instance().AddComponent<T>(GetSceneType(), GetGameObject(), args...);
		}

		// コンポーネントの取得
		template<class T>
		std::weak_ptr<T> GetComponent() {
			return EvaEngine::Internal::ComponentManager::Instance().GetComponent<T>(GetSceneType(), m_GameObjectID);
		}

		// コンポーネントの削除
		template<class T>
		void RemoveComponent() {
			EvaEngine::Internal::ComponentManager::Instance().RemoveComponent<T>(GetSceneType(), m_GameObjectID);
		}

		// 名前で検索
		std::weak_ptr<GameObject> Find(const std::string& name);
		// タグで検索してゲームオブジェクトを一つ持ってくる
		std::weak_ptr<GameObject> FindGameObjectWithTag(const std::string& tag);
		// タグで検索してヒットしたゲームオブジェクトを全部持ってくる
		std::vector<std::weak_ptr<GameObject>> FindGameObjectsWithTag(const std::string& tag);

	private:
		std::weak_ptr<Transform> m_Transform;
		std::string m_Tag{};
		std::string m_Name{};
		UINT m_GameObjectID{};
	};
}