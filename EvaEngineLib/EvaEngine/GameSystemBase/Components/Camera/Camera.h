#pragma once

#include "../../../App/DirectX11App/DirectX11App.h"
#include <DirectXMath.h>
#include "../../Base/Component/Component.h"

#undef near
#undef far

namespace EvaEngine {

	struct Matrix4x4;

	class Camera : public Component
	{
	public:
		Camera(
			const D3D11_VIEWPORT& viewPort,
			const float& near = 0.3f,
			const float& far = 1000.0f,
			const float& fov = 60.0f);
		Camera(
			const float& near = 0.3f,
			const float& far = 1000.0f,
			const float& fov = 60.0f);
		~Camera() = default;

	public:
		void Awake() override;
		void Update() override;

	public:
		// ビューポートを取得
		D3D11_VIEWPORT  GetViewport() const;
		// ビュー行列を取得
		DirectX::XMMATRIX GetViewMatrix() const;
		// プロジェクション行列を取得
		DirectX::XMMATRIX GetProjectionMatrix() const;

		// ビュー行列を作成
		DirectX::XMMATRIX CreateViewMatrix(const std::weak_ptr<Transform>& transform);
		DirectX::XMMATRIX CreateViewMatrix(const Matrix4x4& rotateMatrix, const Matrix4x4& positionMatrix);
		// プロジェクション行列を作成
		DirectX::XMMATRIX CreateProjectionMatrix(
			const D3D11_VIEWPORT& viewPort,
			const float& near,
			const float& far,
			const float& fovDegree);

	private:
		DirectX::XMMATRIX	m_ViewMatrix{};
		DirectX::XMMATRIX	m_ProjectionMatrix{};

		float m_Near{};
		float m_Far{};
		float m_Fov{};
	};
}