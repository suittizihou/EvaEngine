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
		const ComponentDesc& componentDesc,
		const std::weak_ptr<MeshFilter>& meshFilter,
		const std::weak_ptr<Camera>& camera);

	~MeshRenderer() { std::cout << "デストラクタ" << std::endl; }

	void Draw(
		const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& command,
		const ModelApp& modelApp) override;

private:
	My3DLib::Model m_Model{};
	ConstantBuffer m_ConstantBuffer{};
	std::weak_ptr<MeshFilter> m_MeshFilter;
	std::weak_ptr<Transform> m_Transform;
	std::weak_ptr<Camera> m_Camera;
};