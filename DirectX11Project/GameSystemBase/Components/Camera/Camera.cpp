#include "Camera.h"
#include "../../../Setting/Window/Window.h"
#include "../../Base/GameObject/GameObject.h"
#include "../Transform/Transform.h"

using namespace DirectX;
using namespace FunctionMask;

Camera::Camera(
	const D3D11_VIEWPORT& viewPort,
	const float& near_,
	const float& far_,
	const float& fov) :
	Component(UPDATE, false),
	m_Near(near_),
	m_Far(far_),
	m_Fov(fov),
	m_ProjectionMatrix(XMMatrixPerspectiveFovLH(XMConvertToRadians(m_Fov),
		Window::GetViewport().Width / Window::GetViewport().Height, m_Near, m_Far))
{
}

Camera::Camera(
	const float& near_, const float& far_, const float& fov) :
	Component(UPDATE, false),
	m_Near(near_),
	m_Far(far_),
	m_Fov(fov)
{
	m_ProjectionMatrix = XMMatrixPerspectiveFovLH(XMConvertToRadians(m_Fov),
		Window::GetViewport().Width / Window::GetViewport().Height, m_Near, m_Far);
}

void Camera::Awake()
{
	m_ViewMatrix =
		XMMatrixLookAtLH(
			XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f),		// どの方向を見ているか(方向ベクトル)
			XMVectorSet(								// どの場所にカメラがあるか
				GetTransform().lock()->position().x,
				GetTransform().lock()->position().y,
				GetTransform().lock()->position().z,
				0.0f),
			XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
}

void Camera::Update()
{
	// ビュー行列を求める(まだ逆行列をしてない)
	Matrix4x4 viewMatrix = Matrix4x4::translate(GetTransform().lock()->position()) * Matrix4x4::rotate(GetTransform().lock()->rotation());
	//Matrix4x4 viewMatrix = Matrix4x4::look_at(GetTransform().lock()->position(), GetTransform().lock()->forward(), GetTransform().lock()->up());
	// 逆行列にする
	viewMatrix = viewMatrix.inverse();
	// ビュー行列をセット
	m_ViewMatrix = XMMATRIX(
		viewMatrix.m[0][0], viewMatrix.m[0][1], viewMatrix.m[0][2], viewMatrix.m[0][3],
		viewMatrix.m[1][0], viewMatrix.m[1][1], viewMatrix.m[1][2], viewMatrix.m[1][3],
		viewMatrix.m[2][0], viewMatrix.m[2][1], viewMatrix.m[2][2], viewMatrix.m[2][3],
		viewMatrix.m[3][0], viewMatrix.m[3][1], viewMatrix.m[3][2], viewMatrix.m[3][3]);

	// 視錐台の作成
	m_ProjectionMatrix = XMMatrixPerspectiveFovLH(XMConvertToRadians(m_Fov),
		Window::GetViewport().Width / Window::GetViewport().Height, m_Near, m_Far);
}

D3D11_VIEWPORT  Camera::GetViewport() const
{
	return Window::GetViewport();
}

DirectX::XMMATRIX Camera::GetViewMatrix() const
{
	return m_ViewMatrix;
}

DirectX::XMMATRIX Camera::GetProjectionMatrix() const
{
	return m_ProjectionMatrix;
}
