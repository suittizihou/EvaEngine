#pragma once

#include <EvaEngine.h>

class DirectionLight : public EvaEngine::MonoBehaviour {
public:
	DirectionLight() : MonoBehaviour(EvaEngine::FunctionMask::EXECUTE_EDIT_UPDATE) {}
	void Update() override;
#if _DEBUG
	// Editor用の描画関数
	void OnGUI() override;
#endif

private:
	EvaEngine::Vector3 m_LightColor{ EvaEngine::Vector3::one() * 0.5f };
	EvaEngine::Vector3 m_AmbientColor{ EvaEngine::Vector3::one() * 0.1f };
};