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

				void Update() override;

				// シーンビューで使用してるカメラを取得
				std::weak_ptr<Camera> GetSceneCamera();

			private:
				std::weak_ptr<Transform> m_SceneCameraParent;
				std::weak_ptr<Camera> m_SceneCamera;
				float m_Speed{ 5.0f };
			};
		}
	}
}
#endif