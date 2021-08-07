#pragma once

#include <EvaEngine.h>

class SinMove : public EvaEngine::MonoBehaviour {
public:
	SinMove(const float swingWidth, const float speed);
	~SinMove() = default;

public:
	void Awake() override;
	void Update() override;

private:
	EvaEngine::Vector3 m_DefaultPos{};
	float m_Speed{ 0.0f };
	float m_SwingWidth{ 0.0f };
	float m_Counter{ 0.0f };
};