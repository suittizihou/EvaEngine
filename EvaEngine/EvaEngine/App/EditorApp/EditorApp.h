#if _DEBUG
#pragma once

#include <wrl.h>
#include <imgui.h>

namespace EvaEngine {
	class EditorApp {
	public:
		// ‰Šú‰»
		static HRESULT Init();

		// Editor•`‰æ‘O€”õ
		static void DrawBegin();
		// Editor•`‰æˆ—
		static void Draw();
		// Editor•`‰æI—¹
		static void DrawEnd();

		// EditorI—¹ˆ—
		static void End();

	public:
		void EditTransform(float* cameraView, float* cameraProjection, float* matrix, bool editTransformDecomposition);

	private:
		static ImGuiIO& io;
	};
}
#endif