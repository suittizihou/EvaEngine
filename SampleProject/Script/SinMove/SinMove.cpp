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
	m_DefaultPos = GetTransform().lock()->position();
}

void SinMove::Update() {
	GetTransform().lock()->position(m_DefaultPos.x, std::sin(m_Counter) * m_SwingWidth, m_DefaultPos.z);
	m_Counter += m_Speed * Time::GetDeltaTime();
}