#if _DEBUG
#pragma once
#include <memory>


namespace EvaEngine {
	
	class Camera;

	class SceneView {
	public:
		SceneView() = default;
		~SceneView() = default;

		// シーンビューで使用してるカメラを取得
		std::weak_ptr<Camera> GetSceneCamera();

	private:
		std::weak_ptr<Camera> m_SceneCamera;
	};
}

#endif