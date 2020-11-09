#pragma once

#include "../../Base/Scene/Scene.h"

#include <map>
#include <string>
#include <memory>

class SceneDataBase {
private:
	SceneDataBase() = default;
	SceneDataBase(const SceneDataBase&);
	SceneDataBase& operator=(const SceneDataBase&);
	~SceneDataBase() = default;

public:
	static SceneDataBase& Instance() {
		static SceneDataBase instance;
		return instance;
	}

	// シーンの追加
	template<class T>
	void AddScene(const SceneType& sceneType) {
		std::shared_ptr<T> scene = std::make_shared<T>(sceneType);
		m_Scenes[sceneType] = scene;
		ComponentManager::Instance().AddComponentDataBase(sceneType);
		GameObjectManager::Instance().AddGameObjectDataBase(sceneType);
	}

	// シーンのロード
	void LoadScene(const SceneType& sceneType);
	void LoadScene(const UINT& sceneType);
	// 今のシーンのTypeを返す
	SceneType GetCurrentSceneType();
	// シーンの初期化を行う
	void InitializeScene();
	// シーンを変える
	void SceneChange();

	// シーンのタスクシステムを回す
	void Initialize();
	void SceneUpdate();
	void FixedUpdate();
	void Update();
	void LateUpdate();
	void RemoveComponent();
	void Draw(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& command);

private:
	SceneType m_CurrentSceneType{};
	SceneType m_PreviousSceneType{};
	std::weak_ptr<Scene> m_CurrentScene;
	std::map<SceneType, std::shared_ptr<Scene>> m_Scenes;
};