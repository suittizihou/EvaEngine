#pragma once

#include "../../../GameSystemBase/Components/MonoBehaviour/MonoBehaviour.h"

class MoveScript : public MonoBehaviour {
public:
	MoveScript(const float& speed);
	~MoveScript() = default;

	void Update() override;

private:
	float m_Speed{};
};