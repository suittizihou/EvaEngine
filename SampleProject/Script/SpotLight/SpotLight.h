#pragma once

#include <EvaEngine.h>

class SpotLight : public EvaEngine::MonoBehaviour {
public:
	SpotLight() : MonoBehaviour(EvaEngine::FunctionMask::EXECUTE_EDIT_UPDATE) {}

	void Update() override;

#if _DEBUG
	void OnGUI() override;
#endif

private:
	EvaEngine::Vector3 m_Color{ EvaEngine::Vector3(0.1f, 0.1f, 1.0f) };
	float m_Range{ 300.0f };
	float m_Angle{ 25.0f };
};