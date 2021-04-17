#if _DEBUG
#pragma once
#include <memory>

class Camera;

namespace EvaEngine {
	class SceneView {
		SceneView() = default;
		SceneView(const SceneView&);
		SceneView& operator=(const SceneView&);
		~SceneView() = default;

	public:
		static SceneView& Instance() {
			static SceneView instance;
			return instance;
		}

	public:
		// シーンビューで使用してるカメラを取得
		std::weak_ptr<Camera> GetSceneCamera();

	private:
		std::weak_ptr<Camera> m_SceneCamera;
	};
}

#endif