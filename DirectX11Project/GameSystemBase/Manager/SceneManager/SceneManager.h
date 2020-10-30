#ifndef SCENE_MANAGER_H_
#define SCENE_MANAGER_H_

#include "../../Base/Scene/Scene.h"

class SceneManager {
public:
	SceneManager() = default;
	~SceneManager() = default;

	typedef unsigned int UINT;

public:
	static void LoadScene(const SceneType& sceneType);
	static void LoadScene(const UINT& sceneType);
	static SceneType GetCurrentScene();
};

#endif
