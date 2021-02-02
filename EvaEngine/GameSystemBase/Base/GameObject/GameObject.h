#pragma once

#include "GameObjectBase.h"
#include "../../Manager/ComponentManager/ComponentManager.h"

class Transform;

class GameObject final : public GameObjectBase {
public:
	GameObject(
		const SceneType& sceneType = SceneType::None,
		const UINT& gameObjectID = 0,
		const std::string& tag = "",
		const std::string& name = "") :
		GameObjectBase(sceneType),
		m_GameObjectID(gameObjectID),
		m_Tag(tag),
		m_Name(name)
	{};
	
	~GameObject() = default;

	// 初期化処理
	void Initialize() override;

	// ObjectIDを返す
	EVAENGINE_API UINT GetObjectID() const override;
	// 名前を返す
	EVAENGINE_API std::string GetName() const override;
	// タグを返す
	EVAENGINE_API std::string GetTag() const override;
	// Transformを返す
	EVAENGINE_API std::weak_ptr<Transform> GetTransform();

	// コンポーネントの登録
	template<class T, class... Args>
	EVAENGINE_API std::weak_ptr<T> AddComponent(Args&& ... args) {
		return ComponentManager::Instance().AddComponent<T>(GetSceneType(), GetGameObject(), args...);
	}

	// コンポーネントの取得
	template<class T>
	EVAENGINE_API std::weak_ptr<T> GetComponent() {
		return ComponentManager::Instance().GetComponent<T>(GetSceneType(), m_GameObjectID);
	}

	// コンポーネントの削除
	template<class T>
	EVAENGINE_API void RemoveComponent() {
		ComponentManager::Instance().RemoveComponent<T>(GetSceneType(), m_GameObjectID);
	}

	// 名前で検索
	EVAENGINE_API std::weak_ptr<GameObject> Find(const std::string& name);
	// タグで検索してゲームオブジェクトを一つ持ってくる
	EVAENGINE_API std::weak_ptr<GameObject> FindGameObjectWithTag(const std::string& tag);
	// タグで検索してヒットしたゲームオブジェクトを全部持ってくる
	EVAENGINE_API std::vector<std::weak_ptr<GameObject>> FindGameObjectsWithTag(const std::string& tag);

private:
	std::weak_ptr<Transform> m_Transform;
	std::string m_Tag{};
	std::string m_Name{};
	UINT m_GameObjectID{};
};