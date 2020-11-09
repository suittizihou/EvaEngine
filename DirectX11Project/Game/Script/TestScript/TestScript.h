#pragma once

#include "../../../GameSystemBase/Components/MonoBehaviour/MonoBehaviour.h"

class TestScript : public MonoBehaviour {
public:
	TestScript();
	~TestScript() = default;

	void Awake() override;
};