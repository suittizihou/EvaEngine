#include "Rotate.h"

using namespace EvaEngine;

void Rotate::Awake()
{
	m_Camera = Instantiate("Main Camera").lock()->GetComponent<Transform>();
	m_Camera.lock()->parent(GetTransform());
	m_Camera.lock()->GetGameObject().lock()->AddComponent<Camera>();
}

void Rotate::Update()
{
	auto transform = GetTransform();
	Vector3 xAxis{}, yAxis{};
	if (Input::GetKey(KeyCode::UpArrow)) { xAxis += Vector3::left(); }
	if (Input::GetKey(KeyCode::DownArrow)) { xAxis += Vector3::right(); }
	if (Input::GetKey(KeyCode::LeftArrow)) { yAxis += Vector3::down(); }
	if (Input::GetKey(KeyCode::RightArrow)) { yAxis += Vector3::up(); }

	m_Camera.lock()->rotate(xAxis * m_Speed);
	transform.lock()->rotate(yAxis * m_Speed);
}
