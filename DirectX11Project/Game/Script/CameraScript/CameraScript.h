#pragma once

#include "../../../GameSystemBase/Components/MonoBehaviour/MonoBehaviour.h"
#include "../../../Utility/Math/Vector3/Vector3.h"

class CameraScript : public MonoBehaviour {
public:
	CameraScript(const Vector3& position, const Vector3& euler);
	~CameraScript() = default;

	void Awake() override;
	void Update() override;

private:
	Vector3 m_Position{};
	Vector3 m_Euler{};
	std::weak_ptr<GameObject> m_GameObject;
};