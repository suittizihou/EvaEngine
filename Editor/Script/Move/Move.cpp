#include "Move.h"

using namespace EvaEngine;

void Move::Update()
{
	Vector3 velocity{};
	auto transform = GetTransform().lock();

	if (Input::GetKey(KeyCode::A)) {
		velocity += transform->left() * m_Speed;
	}

	if (Input::GetKey(KeyCode::D)) {
		velocity += transform->right() * m_Speed;
	}

	if (Input::GetKey(KeyCode::W)) {
		velocity += transform->forward() * m_Speed;
	}

	if (Input::GetKey(KeyCode::S)) {
		velocity += transform->back() * m_Speed;
	}

	transform->move(velocity);
}
