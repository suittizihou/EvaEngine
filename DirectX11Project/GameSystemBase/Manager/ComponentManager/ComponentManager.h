#pragma once

#include <string>
#include <list>
#include <queue>
#include <map>
#include <memory>
#include <stdexcept>
#include <functional>
#include "../../Base/Component/Component.h"
#include "../../DataBase/ComponentDataBase/ComponentDataBase.h"
#include "../../Base/GameObject/GameObjectBase.h"
#include "../../Base/Scene/SceneType.h"

class ComponentManager {
private:
	ComponentManager() = default;
	ComponentManager(const ComponentManager&);
	ComponentManager& operator=(const ComponentManager&);
	~ComponentManager() = default;

public:
	static ComponentManager& Instance() {
		static ComponentManager componentManager;
		return componentManager;
	}

	// コンポーネントデータベースをシーンに追加
	void AddComponentDataBase(const SceneType& sceneType);

	// コンポーネントの登録
	template<class T, class... Args>
	std::weak_ptr<T> AddComponent(const SceneType& sceneType, const std::weak_ptr<GameObjectBase>& gameObject, Args&& ... args)
	{
		return m_ComponentList[sceneType]->AddComponent<T>(sceneType, gameObject, args...);
	}

	// コンポーネントの取得
	template<class T>
	std::weak_ptr<T> GetComponent(const SceneType& sceneType, const UINT& gameObjectID)
	{
		return m_ComponentList[sceneType]->GetComponent<T>(gameObjectID);
	}

	// コンポーネントを削除
	template<class T>
	void RemoveComponent(const SceneType& sceneType, const UINT& gameObjectID)
	{
		m_ComponentList[sceneType]->RemoveComponent<T>(gameObjectID);
	}

	// 保持しているコンポーネントを全部削除
	void RemoveAllComponent(const SceneType& sceneType);

	// FixedUpdate関数を回す
	void FixedUpdate(const SceneType& sceneType);
	// Update関数を回す
	void Update(const SceneType& sceneType);
	// LateUpdate関数を回す
	void LateUpdate(const SceneType& sceneType);
	// Draw関数を回す
	void Draw(
		const SceneType& sceneType,
		const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& command);

private:
	// コンポーネントのリスト(firstはオブジェクトID)
	std::map<SceneType,		// GameObjectID
		std::shared_ptr<ComponentDataBase>> m_ComponentList;

	UINT m_ComponentID{};
};