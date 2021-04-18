#if _DEBUG
#pragma once

#include <d3d11.h>
#include <wrl.h>
#include <imgui.h>
#include <memory>

namespace EvaEngine {
	class SceneView;

	class EditorApp {
	public:
		// ‰Šú‰»
		static HRESULT Init();

		// Editor•`‰æ‘O€”õ
		static void DrawBegin();
		// Editor•`‰æˆ—
		static void Draw(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& command);
		// Editor•`‰æI—¹
		static void DrawEnd();

		// EditorI—¹ˆ—
		static void End();

	public:
		void EditTransform(float* cameraView, float* cameraProjection, float* matrix, bool editTransformDecomposition);

	private:
		static std::unique_ptr<SceneView> m_SceneView;
	};
}
#endif