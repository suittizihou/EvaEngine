#ifndef CAMERA_H_
#define CAMERA_H_

#include "../../../App/DirectX11App/DirectX11App.h"
#include <DirectXMath.h>
#include "../../Base/Component/Component.h"

class Camera : public Component
{
public:
	Camera(
		const ComponentDesc& componentDesc,
		const D3D11_VIEWPORT& viewPort,
		const float& near_,
		const float& far_,
		const float& fov);
	Camera(
		const ComponentDesc& componentDesc,
		const float& near_,
		const float& far_,
		const float& fov);
	~Camera() = default;

public:
	void Update() override;

public:
	D3D11_VIEWPORT  GetViewport() const;
	DirectX::XMMATRIX GetViewMatrix() const;
	DirectX::XMMATRIX GetProjectionMatrix() const;

private:
	D3D11_VIEWPORT		m_Viewport{};
	DirectX::XMMATRIX	m_ViewMatrix{};
	DirectX::XMMATRIX	m_ProjectionMatrix{};
	RECT m_Rect{};

	float m_Near{};
	float m_Far{};
	float m_Fov{};
};

#endif