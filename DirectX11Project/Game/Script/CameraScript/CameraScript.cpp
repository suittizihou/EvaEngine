#include "CameraScript.h"

#include "../../../GameSystemBase/Base/GameObject/GameObject.h"
#include "../../../GameSystemBase/Components/ComponentHeaders.h"

#include "../MoveScript/MoveScript.h"
#include "../SinMove/SinMove.h"

CameraScript::CameraScript(const Vector3& position, const Vector3& euler) :
	MonoBehaviour(FunctionMask::UPDATE),
	m_Position(position),
	m_Euler(euler)
{
}

void CameraScript::Awake()
{
	GetGameObject().lock()->AddComponent<Camera>();
	GetGameObject().lock()->AddComponent<MoveScript>(0.001f);
	GetTransform().lock()->position(m_Position);
	GetTransform().lock()->euler_angles(m_Euler);
}

void CameraScript::Update()
{
	if (Input::GetKey(KeyCode::UpArrow)) {
		GetTransform().lock()->rotate(-0.1f, 0.0f, 0.0f);
	}
	if (Input::GetKey(KeyCode::DownArrow)) {
		GetTransform().lock()->rotate(0.1f, 0.0f, 0.0f);
	}
	if (Input::GetKey(KeyCode::LeftArrow)) {
		GetTransform().lock()->rotate(0.0f, -0.1f, 0.0f, Transform::Space::World);
	}
	if (Input::GetKey(KeyCode::RightArrow)) {
		GetTransform().lock()->rotate(0.0f, 0.1f, 0.0f, Transform::Space::World);
	}

	// プレイヤーの座標を見る
	//GetTransform().lock()->look_at(FindGameObjectWithTag("Player").lock()->GetTransform().lock()->position());

	if (Input::GetKeyDown(KeyCode::Y)) {
		auto obj = AddGameObject();
		obj.lock()->GetTransform().lock()->position(GetTransform().lock()->position());
		obj.lock()->GetTransform().lock()->local_scale(Vector3(0.1f, 0.1f, 0.1f));
		obj.lock()->AddComponent<SinMove>(0.0025f, 0.0003f);
		obj.lock()->AddComponent<MeshRenderer>(obj.lock()->AddComponent<MeshFilter>(1), GetGameObject().lock()->GetComponent<Camera>());
		m_GameObject = obj;
	}

	if (Input::GetKeyDown(KeyCode::U)) {
		m_GameObject.lock()->RemoveComponent<SinMove>();
	}

	if (Input::GetKeyDown(KeyCode::I)) {
		FindGameObjectWithTag("Player").lock()->RemoveComponent<MeshRenderer>();
	}
}
