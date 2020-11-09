#pragma once

#include <DirectXMath.h>
#include <iostream>

#include "../../Base/Component/Component.h"
#include "../../../Utility/ModelUtility/ModelData/ModelData.h"

class MeshFilter;
class Transform;
class Camera;

class MeshRenderer : public Component {
public:
	MeshRenderer(
		const std::weak_ptr<MeshFilter>& meshFilter,
		const std::weak_ptr<Camera>& camera);

	~MeshRenderer() { std::cout << "デストラクタ" << std::endl; }

	void Awake() override;
	void Draw(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& command) override;

private:
	My3DLib::Model m_Model{};
	std::weak_ptr<MeshFilter> m_MeshFilter;
	std::weak_ptr<Transform> m_Transform;
	std::weak_ptr<Camera> m_Camera;
};