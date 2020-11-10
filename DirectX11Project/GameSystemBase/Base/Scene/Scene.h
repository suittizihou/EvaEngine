#pragma once

#include "../../Manager/ComponentManager/ComponentManager.h"
#include "../../Manager/GameObjectManager/GameObjectManager.h"

#include "SceneType.h"

class Scene {
public:
	Scene(const SceneType& sceneType) : m_SceneType(sceneType) {};
	virtual ~Scene() = default;

public:
	// シーンの初期化
	virtual void Initialize() = 0;

	// シーンのアップデート
	virtual void SceneUpdate() = 0;

	// 固定更新処理
	void FixedUpdate() {
		ComponentManager::Instance().FixedUpdate(m_SceneType);
	}

	// 更新処理
	void Update() {
		ComponentManager::Instance().Update(m_SceneType);
	};

	// 遅延更新処理
	void LateUpdate() {
		ComponentManager::Instance().LateUpdate(m_SceneType);
	}

	// コンポーネント削除処理
	void RemoveComponent() {
		ComponentManager::Instance().RunRemoveComponents(m_SceneType);
	}

	// 描画処理
	void Draw(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& command)
	{
		ComponentManager::Instance().Draw(m_SceneType, command);
	};

	// 名前で検索
	std::weak_ptr<GameObject> Find(const std::string& name);
	// タグで検索してゲームオブジェクトを一つ持ってくる
	std::weak_ptr<GameObject> FindGameObjectWithTag(const std::string& tag);
	// タグで検索してヒットしたゲームオブジェクトを全部持ってくる
	std::vector<std::weak_ptr<GameObject>> FindGameObjectsWithTag(const std::string& tag);


	std::weak_ptr<GameObject> AddGameObject(const std::string& name = "GameObject", const std::string& tag = "None");

protected:
	SceneType m_SceneType{};
};