#pragma once

#include "../../../GameSystemBase/Base/Scene/Scene.h"

class GameMain : public Scene {
public:
	GameMain(const SceneType& sceneType);
	~GameMain() = default;

	void Initialize() override;
	void SceneUpdate() override;
};