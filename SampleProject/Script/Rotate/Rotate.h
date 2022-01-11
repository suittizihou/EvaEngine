#pragma once

#include <EvaEngine.h>

class Rotate : public EvaEngine::MonoBehaviour {
public:
	Rotate(float speed) : MonoBehaviour(EvaEngine::FunctionMask::UPDATE), m_Speed{ speed } {}

	void Awake() override;
	void Update() override;

private:
	std::weak_ptr<EvaEngine::Transform> m_Child;
	float m_Speed{};
};