#pragma once
#include <EvaEngine.h>

class SampleScene : public EvaEngine::Scene {
public:
	SampleScene(const std::u8string& sceneName, const UINT sceneID);

	void Initialize() override;
	void SceneUpdate() override;
};