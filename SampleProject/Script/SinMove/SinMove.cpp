#include "SinMove.h"

using namespace EvaEngine;

SinMove::SinMove(const float swingWidth, const float speed) : 
	MonoBehaviour(FunctionMask::UPDATE),
	m_Speed{ speed },
	m_SwingWidth{ swingWidth }
{
}

void SinMove::Awake()
{
	Vector3 position = GetTransform().lock()->position();
	m_DefaultPos = position;
	m_Counter = (position.x + position.z) * 0.1f;
}

void SinMove::Update() {
	GetTransform().lock()->position(m_DefaultPos.x, std::sin(m_Counter) * m_SwingWidth, m_DefaultPos.z);
	m_Counter += 1.0f * Time::GetDeltaTime();
}