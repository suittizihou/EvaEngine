#if _DEBUG
#include "SceneView.h"
#include "../../GameSystemBase/Base/GameObject/GameObject.h"
#include "../../GameSystemBase/Manager/GameObjectManager/GameObjectManager.h"
#include "../../GameSystemBase/Components/Camera/Camera.h"
#include "../../GameSystemBase/Components/Transform/Transform.h"
#include "../../Utility/Input/Input.h"
#include "../../Utility/Math/Vector3/Vector3.h"
#include "../../Utility/Time/Time.h"

EvaEngine::Editor::Internal::SceneView::SceneView() : EvaEngine::Component(EvaEngine::FunctionMask::UPDATE)
{
	m_SceneCameraParent = EvaEngine::Internal::GameObjectManager::Instance().
		Instantiate("Editor", "SceneView", "SceneViewParent").lock()->GetComponent<Transform>();

	m_SceneCameraParent.lock()->set_parent(GetTransform(), false);
	m_SceneCamera = m_SceneCameraParent.lock()->GetGameObject().lock()->AddComponent<Camera>();
}

void EvaEngine::Editor::Internal::SceneView::Update() {

	// ˆÚ“®
	Vector3 velocity{};
	auto transform = GetTransform().lock();

	if (Input::GetKey(KeyCode::A)) { velocity += transform->left(); }
	if (Input::GetKey(KeyCode::D)) { velocity += transform->right(); }
	if (Input::GetKey(KeyCode::W)) { velocity += transform->forward(); }
	if (Input::GetKey(KeyCode::S)) { velocity += transform->back(); }
	if (Input::GetKey(KeyCode::E)) { velocity += Vector3::up(); }
	if (Input::GetKey(KeyCode::Q)) { velocity += Vector3::down(); }

	transform->move(velocity * m_Speed * Time::GetDeltaTime());

	// ‰ñ“]
	Vector3 xAxis{}, yAxis{};
	if (Input::GetKey(KeyCode::UpArrow)) { xAxis += Vector3::left(); }
	if (Input::GetKey(KeyCode::DownArrow)) { xAxis += Vector3::right(); }
	if (Input::GetKey(KeyCode::LeftArrow)) { yAxis += Vector3::down(); }
	if (Input::GetKey(KeyCode::RightArrow)) { yAxis += Vector3::up(); }

	float deltaTime = Time::GetDeltaTime();
	m_SceneCameraParent.lock()->rotate(xAxis * m_Speed * deltaTime);
	transform->rotate(yAxis * m_Speed * deltaTime);
}

std::weak_ptr<EvaEngine::Camera> EvaEngine::Editor::Internal::SceneView::GetSceneCamera()
{
	return m_SceneCamera;
}
#endif