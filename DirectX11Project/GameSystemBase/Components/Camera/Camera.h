#pragma once

#include "../../../App/DirectX11App/DirectX11App.h"
#include <DirectXMath.h>
#include "../../Base/Component/Component.h"

class Camera : public Component
{
public:
	Camera(
		const D3D11_VIEWPORT& viewPort,
		const float& near_,
		const float& far_,
		const float& fov);
	Camera(
		const float& near_ = 0.3f,
		const float& far_ = 1000.0f,
		const float& fov = 60.0f);
	~Camera() = default;

public:
	void Awake() override;
	void Update() override;

public:
	D3D11_VIEWPORT  GetViewport() const;
	DirectX::XMMATRIX GetViewMatrix() const;
	DirectX::XMMATRIX GetProjectionMatrix() const;

private:
	DirectX::XMMATRIX	m_ViewMatrix{};
	DirectX::XMMATRIX	m_ProjectionMatrix{};
	RECT m_Rect{};

	float m_Near{};
	float m_Far{};
	float m_Fov{};
};