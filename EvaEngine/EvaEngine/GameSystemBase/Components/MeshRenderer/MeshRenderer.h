#pragma once

#include <DirectXMath.h>
#include <iostream>

#include "../../Base/Component/Component.h"
#include "../../../Utility/ModelUtility/ModelData/ModelData.h"

namespace EvaEngine {

	class MeshFilter;
	class Transform;
	class Camera;

	class MeshRenderer : public Component {
	public:
		MeshRenderer(
			const std::weak_ptr<MeshFilter>& meshFilter);

		~MeshRenderer() { std::cout << "デストラクタ" << std::endl; }

		void Awake() override;
		void Draw(const std::weak_ptr<Camera> camera, const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& command) override;

#if _DEBUG
		void OnGUI() override;
#endif

	private:
		ModelData m_Model{};
		std::weak_ptr<MeshFilter> m_MeshFilter;
		std::weak_ptr<Transform> m_Transform;
	};
}