#if _DEBUG
#include "SceneView.h"
#include "../../GameSystemBase/Base/GameObject/GameObject.h"
#include "../../GameSystemBase/Manager/GameObjectManager/GameObjectManager.h"
#include "../../GameSystemBase/Components/Camera/Camera.h"
#include "../../GameSystemBase/Components/Transform/Transform.h"
#include "../../Utility/Input/Input.h"
#include "../../Utility/Math/Vector3/Vector3.h"
#include "../../Utility/Time/Time.h"
#include "../../Editor/EditorApplication/EditorApplication.h"

EvaEngine::Editor::Internal::SceneView::SceneView() : EvaEngine::Component(EvaEngine::FunctionMask::UPDATE)
{
}

void EvaEngine::Editor::Internal::SceneView::Awake()
{
	m_SceneCameraObj = EvaEngine::Internal::GameObjectManager::Instance().
		Instantiate("Editor", "SceneView", "SceneViewParent").lock()->GetComponent<Transform>();

	m_SceneCameraObj.lock()->set_parent(GetTransform(), false);
	m_SceneCamera = m_SceneCameraObj.lock()->GetGameObject().lock()->AddComponent<Camera>();
	m_SceneCamera.lock()->clearColor = Color::Black();
}

void EvaEngine::Editor::Internal::SceneView::Update() {

	// SceneWindowが非アクティブの時は返す
	if (EvaEngine::Editor::EditorApplication::sceneWindowIsActive == false) return;

	// 移動
	Vector3 velocity{};
	auto transform = GetTransform().lock();
	float deltaTime = Time::GetDeltaTime();

	if (Input::GetKey(KeyCode::A)) { velocity += transform->left(); }
	if (Input::GetKey(KeyCode::D)) { velocity += transform->right(); }
	if (Input::GetKey(KeyCode::W)) { velocity += transform->forward(); }
	if (Input::GetKey(KeyCode::S)) { velocity += transform->back(); }
	if (Input::GetKey(KeyCode::E)) { velocity += Vector3::up(); }
	if (Input::GetKey(KeyCode::Q)) { velocity += Vector3::down(); }

	transform->move(velocity * m_MoveSpeed * deltaTime);

	// 回転
	Vector3 xAxis{}, yAxis{};
	if (Input::GetKey(KeyCode::UpArrow)) { xAxis += Vector3::left(); }
	if (Input::GetKey(KeyCode::DownArrow)) { xAxis += Vector3::right(); }
	if (Input::GetKey(KeyCode::LeftArrow)) { yAxis += Vector3::down(); }
	if (Input::GetKey(KeyCode::RightArrow)) { yAxis += Vector3::up(); }

	m_SceneCameraObj.lock()->rotate(xAxis * m_RotateSpeed * deltaTime);
	transform->rotate(yAxis * m_RotateSpeed * deltaTime);
}

std::weak_ptr<EvaEngine::Camera> EvaEngine::Editor::Internal::SceneView::GetSceneCamera()
{
	return m_SceneCamera;
}
#endif