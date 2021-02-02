#pragma once

#include "../../Base/Scene/Scene.h"

class SceneManager {
public:
	SceneManager() = default;
	~SceneManager() = default;

	typedef unsigned int UINT;

public:
	EVAENGINE_API static void LoadScene(const SceneType& sceneType);
	EVAENGINE_API static void LoadScene(const UINT& sceneType);
	EVAENGINE_API static SceneType GetCurrentScene();
};