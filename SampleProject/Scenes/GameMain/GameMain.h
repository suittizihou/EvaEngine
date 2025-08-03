#pragma once
#include <EvaEngine.h>

class GameMain : public EvaEngine::Scene {
public:
	GameMain(const std::u8string& sceneName, const UINT sceneID);
	~GameMain();

	void Initialize() override;
	void SceneUpdate() override;
};