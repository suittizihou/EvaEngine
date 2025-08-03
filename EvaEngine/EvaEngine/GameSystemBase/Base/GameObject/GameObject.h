#pragma once

#include "GameObjectBase.h"
#include "../../Manager/ComponentManager/ComponentManager.h"
#include "../../../System/DebugLog/DebugLog.h"

namespace EvaEngine {

	class Transform;

	class GameObject final : public GameObjectBase {
	public:
		GameObject(
			const std::u8string& sceneName = u8"",
			const GUID& guid = GUID_NULL,
			const std::string& tag = "",
			const std::u8string& name = u8"") :
			GameObjectBase(sceneName),
			m_GUID{ guid },
			m_Tag{ tag },
			m_Name{ name }
		{};

		~GameObject() = default;

		// 初期化処理
		void Initialize() override;

		// ObjectIDを返す
		const GUID& GetObjectID() const override;
		// 名前を返す
		std::u8string GetName() const override;
		// タグを返す
		std::string GetTag() const override;
		// Transformを返す
		std::weak_ptr<Transform> GetTransform();

		// コンポーネントの登録
		template<class T, class... Args>
		std::weak_ptr<T> AddComponent(Args&& ... args) {
			static_assert(std::is_base_of<Component, T>::value == true, "The argument does not inherit from Component.");
			auto component = EvaEngine::Internal::ComponentManager::Instance().AddComponent<T>(GetSceneName(), GetGameObject(), args...);
			m_Components.push_back(component);
			return component;
		}

		// コンポーネントの取得
		template<class T>
		std::weak_ptr<T> GetComponent() {
			return EvaEngine::Internal::ComponentManager::Instance().GetComponent<T>(GetSceneName(), GetGameObject());
		}

		std::vector<std::weak_ptr<Component>> GetAllComponents() override { return m_Components; };

		// コンポーネントの削除
		template<class T>
		void RemoveComponent() {
			EvaEngine::Internal::ComponentManager::Instance().RemoveComponent<T>(GetSceneName(), weak_from_this());
			
			// 参照が切れたコンポーネントを配列から削除
			for (int i = 0; i < m_Components.size(); ++i)
			{
				if (m_Components[i].expired()) {
					// 消す場所と末尾をクルっと入れ替え
					std::ranges::iter_swap(m_Components.begin() + i, m_Components.end() - 1);
					// 末尾を削除
					m_Components.pop_back();
					return;
				}
			}

			DebugLog::LogError("GameObject側のComponent削除に失敗しました。");
		}

		// 名前で検索
		std::weak_ptr<GameObject> Find(const std::u8string& name);
		// タグで検索してゲームオブジェクトを一つ持ってくる
		std::weak_ptr<GameObject> FindGameObjectWithTag(const std::string& tag);
		// タグで検索してヒットしたゲームオブジェクトを全部持ってくる
		std::vector<std::weak_ptr<GameObject>> FindGameObjectsWithTag(const std::string& tag);
		// オブジェクトのアクティブ状態を設定
		void SetActive(const bool active);
		// オブジェクトのアクティブ状態を取得
		bool ActiveSelf() const;

	private:
		std::vector<std::weak_ptr<Component>> m_Components;
		std::weak_ptr<Transform> m_Transform;
		std::string m_Tag{};
		std::u8string m_Name{};
		bool m_IsActive{ true };
		GUID m_GUID{};
	};
}