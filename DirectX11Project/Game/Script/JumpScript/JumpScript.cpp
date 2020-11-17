#include "JumpScript.h"
#include "../../../GameSystemBase/Components/Transform/Transform.h"

JumpScript::JumpScript() : MonoBehaviour(FunctionMask::UPDATE)
{
}

void JumpScript::Awake() {
	m_DefaultPosY = GetTransform().lock()->position().y;
}

void JumpScript::Update()
{
	if (m_IsJump) {
		m_Counter += m_JumpSpeed;
		m_PositionY = -(m_Counter * m_Counter) + m_MaxPoint;

		if (m_PositionY <= 0.0f) {
			m_PositionY = 0.0f;
			m_Counter = 0.0f;
			m_IsJump = false;
		}
	}
	else {
		if (Input::GetKeyDown(KeyCode::Space)) {
			m_IsJump = true;
		}
	}

	GetTransform().lock()->move(Vector3(0.0f, m_PositionY, 0.0f));
	Vector3 pos = GetTransform().lock()->position();
}