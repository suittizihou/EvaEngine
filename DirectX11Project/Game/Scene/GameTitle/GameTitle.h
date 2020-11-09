#pragma once

#include "../../../GameSystemBase/Base/Scene/Scene.h"

class GameTitle : public Scene {
public:
	GameTitle(const SceneType& sceneType);
	~GameTitle() = default;

	void Initialize() override;
	void SceneUpdate() override;
};