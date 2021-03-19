#pragma once

#include "../../Base/Scene/Scene.h"
#include "../../DataBase/SceneDataBase/SceneDataBase.h"

class SceneManager {
public:
	SceneManager() = default;
	~SceneManager() = default;

	typedef unsigned int UINT;

public:
	// シーンの追加
	template<class T>
	static void AddScene(const SceneType& sceneType) {
		SceneDataBase::Instance().AddScene<T>(sceneType);
	}

	// シーンのロード
	static void LoadScene(const SceneType& sceneType);
	static void LoadScene(const UINT& sceneType);
	
	// 現在のシーンを取得
	static SceneType GetCurrentScene();
};