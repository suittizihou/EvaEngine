#pragma once
#include <EvaEngine.h>

class EditorEntry : public EvaEngine::GameBase {
public:
	EditorEntry() : GameBase(640, 480) {};

	void Init() override;
};

EditorEntry editorEntry;