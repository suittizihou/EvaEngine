#pragma once
#include <EvaEngine.h>

class EditorEntry : public EvaEngine::GameBase {
public:
	EditorEntry() : GameBase(1280, 720) {};

	void Init() override;
};

EditorEntry editorEntry;