#pragma once
#include <EvaEngine.h>

class EditorEntry : public EvaEngine::GameBase {
public:
	EditorEntry() : GameBase(1920, 1080) {};

	void Init() override;
};

struct MemoryLeakDetector {
	MemoryLeakDetector() {
#if _DEBUG
	// メモリリーク検出
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// リークが報告されたメモリ割り当て番号にブレークポイントを設定
	//_CrtSetBreakAlloc(1067);
#endif
	}
};

MemoryLeakDetector g_MemoryLeakDetector;
EditorEntry g_EditorEntry;