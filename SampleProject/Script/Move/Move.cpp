#include "Move.h"

using namespace EvaEngine;

void Move::Update()
{
	Vector3 velocity{};
	auto transform = GetTransform().lock();

	if (Input::GetKey(KeyCode::A)) { velocity += transform->left(); }
	if (Input::GetKey(KeyCode::D)) { velocity += transform->right(); }
	if (Input::GetKey(KeyCode::W)) { velocity += transform->forward(); }
	if (Input::GetKey(KeyCode::S)) { velocity += transform->back(); }
	if (Input::GetKey(KeyCode::E)) { velocity += Vector3::up(); }
	if (Input::GetKey(KeyCode::Q)) { velocity += Vector3::down(); }
	
	if (Input::GetKeyDown(KeyCode::Space)) DebugLog::Log(u8"Spaceキーを押したよ!");
	transform->move(velocity * m_Speed * Time::GetDeltaTime());
}