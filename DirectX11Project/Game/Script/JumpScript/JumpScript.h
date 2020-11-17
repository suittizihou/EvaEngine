#pragma once

#include "../../../GameSystemBase/Components/MonoBehaviour/MonoBehaviour.h"

class JumpScript : public MonoBehaviour {
public:
	JumpScript();
	~JumpScript() = default;

	void Awake() override;
	void Update() override;

private:
	float m_MaxPoint{ 0.1f };
	float m_Counter{};
	float m_JumpSpeed{ 0.001f };
	float m_PositionY{};
	float m_DefaultPosY{};
	bool m_IsJump{};
};