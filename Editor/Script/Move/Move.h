#pragma once

#include <EvaEngine.h>

class Move : public EvaEngine::MonoBehaviour {
public:
	Move(const float speed) : EvaEngine::MonoBehaviour(EvaEngine::FunctionMask::UPDATE), m_Speed{ speed } {}

	void Update() override;

private:
	float m_Speed{};
};