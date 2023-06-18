#if _DEBUG
#pragma once
#include <memory>
#include "../../GameSystemBase/Base/Component/Component.h"

namespace EvaEngine {
	class Camera;
	class Transform;
	namespace Editor {
		namespace Internal {

			class SceneView : public EvaEngine::Component {
			public:
				SceneView();
				~SceneView() = default;

				void Awake() override;
				void Update() override;

				// �V�[���r���[�Ŏg�p���Ă�J�������擾
				std::weak_ptr<Camera> GetSceneCamera();

			private:
				std::weak_ptr<Transform> m_SceneCameraObj;
				std::weak_ptr<Camera> m_SceneCamera;
				float m_MoveSpeed{ 5.0f };
				float m_RotateSpeed{ 50.0f };
			};
		}
	}
}
#endif