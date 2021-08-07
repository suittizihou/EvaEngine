#pragma once
#include <EvaEngine.h>

class EditorEntry : public EvaEngine::GameBase {
public:
	EditorEntry() : GameBase(1920, 1080) {};

	void Init() override;
};

EditorEntry editorEntry;