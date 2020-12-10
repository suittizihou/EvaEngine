#include "SinMove.h"
#include "../../../GameSystemBase/Components/ComponentHeaders.h"
#include <cmath>

SinMove::SinMove(float speed, float magnitude) : 
	MonoBehaviour(FunctionMask::UPDATE),
	m_Speed(speed),
	m_Magnitude(magnitude)
{
}

void SinMove::Update()
{
	GetTransform().lock()->move(Vector3::right() * std::sin(m_MoveCounter) * m_Magnitude);
	m_MoveCounter += m_Speed;
}
