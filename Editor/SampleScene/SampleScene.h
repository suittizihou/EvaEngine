#pragma once
#include <EvaEngine.h>

class SampleScene : public EvaEngine::Scene {
public:
	SampleScene(const std::string sceneName, const UINT sceneID);

	void Initialize() override;
	void SceneUpdate() override;
};