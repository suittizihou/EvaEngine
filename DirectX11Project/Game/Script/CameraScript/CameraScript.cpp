#include "CameraScript.h"

#include "../../../GameSystemBase/Base/GameObject/GameObject.h"
#include "../../../GameSystemBase/Components/ComponentHeaders.h"

CameraScript::CameraScript(const Vector3& position, const Vector3& euler) :
	MonoBehaviour(FunctionMask::UPDATE),
	m_Position(position),
	m_Euler(euler)
{
}

void CameraScript::Awake()
{
	GetGameObject().lock()->AddComponent<Camera>();
	GetTransform().lock()->move(m_Position);
	GetTransform().lock()->euler_angles(m_Euler);
}

void CameraScript::Update()
{
	if (Input::GetKey(KeyCode::UpArrow)) {
		GetTransform().lock()->rotate(0.1f, 0.0f, 0.0f);
	}
	if (Input::GetKey(KeyCode::DownArrow)) {
		GetTransform().lock()->rotate(-0.1f, 0.0f, 0.0f);
	}
	Vector3 euler = GetTransform().lock()->euler_angles();
}
