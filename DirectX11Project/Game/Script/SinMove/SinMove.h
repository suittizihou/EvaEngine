#pragma once

#include "../../../GameSystemBase/Components/MonoBehaviour/MonoBehaviour.h"

class SinMove : public MonoBehaviour {
public:
    SinMove(float speed, float magnitude);
    ~SinMove() = default;

    void Update() override;

private:
    float m_MoveCounter{};
    float m_Speed{};
    float m_Magnitude{};
};