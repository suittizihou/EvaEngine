#pragma once

#include "../../../GameSystemBase/Components/MonoBehaviour/MonoBehaviour.h"

class JumpScript : public MonoBehaviour {
public:
	JumpScript();
	~JumpScript() = default;

	void Awake() override;
	void Update() override;
};