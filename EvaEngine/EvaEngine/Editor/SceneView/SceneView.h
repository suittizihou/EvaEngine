#if _DEBUG
#pragma once
#include <memory>


namespace EvaEngine {
	class Camera;
	namespace Editor {
		namespace Internal {

			class SceneView {
			public:
				SceneView() = default;
				~SceneView() = default;

				// �V�[���r���[�Ŏg�p���Ă�J�������擾
				std::weak_ptr<Camera> GetSceneCamera();

			private:
				std::weak_ptr<Camera> m_SceneCamera;
			};
		}
	}
}
#endif