#include "Rotate.h"

using namespace EvaEngine;

void Rotate::Awake()
{
	m_Child = GetTransform().lock()->get_child(0);
}

void Rotate::Update()
{
	auto transform = GetTransform();
	Vector3 xAxis{}, yAxis{};
	if (Input::GetKey(KeyCode::UpArrow)) { xAxis += Vector3::left(); }
	if (Input::GetKey(KeyCode::DownArrow)) { xAxis += Vector3::right(); }
	if (Input::GetKey(KeyCode::LeftArrow)) { yAxis += Vector3::down(); }
	if (Input::GetKey(KeyCode::RightArrow)) { yAxis += Vector3::up(); }

	float deltaTime = Time::GetDeltaTime();
	m_Child.lock()->rotate(xAxis * m_Speed * deltaTime);
 	transform.lock()->rotate(yAxis * m_Speed * deltaTime);
}
