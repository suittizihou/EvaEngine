#pragma once

#include <EvaEngine.h>

class PointLight : public EvaEngine::MonoBehaviour {
public:
	PointLight() : MonoBehaviour(EvaEngine::FunctionMask::EXECUTE_EDIT_UPDATE) {};
	void Update() override;
#if _DEBUG
	void OnGUI() override;
#endif

private:
	EvaEngine::Vector3 m_Color{ EvaEngine::Vector3::right()};
	float m_Range{ 10.0f };
};