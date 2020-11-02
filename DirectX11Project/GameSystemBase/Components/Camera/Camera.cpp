#include "Camera.h"
#include "../../../Setting/Window/Window.h"
#include "../../Base/GameObject/GameObject.h"
#include "../Transform/Transform.h"

using namespace DirectX;
using namespace FunctionMask;

Camera::Camera(
	const ComponentDesc& componentDesc,
	const D3D11_VIEWPORT& viewPort,
	const float& near_,
	const float& far_,
	const float& fov) :
	Component(componentDesc, UPDATE, false),
	m_Viewport(viewPort),
	m_Near(near_),
	m_Far(far_),
	m_Fov(fov),
	m_ViewMatrix(
		XMMatrixLookAtLH(
		XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f),		// どの方向を見ているか(方向ベクトル)
		XMVectorSet(								// どの場所にカメラがあるか
			GetTransform().lock()->position().x, 
			GetTransform().lock()->position().y,
			GetTransform().lock()->position().z,
			0.0f),
		XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f))),		// カメラの上向き方向

	m_ProjectionMatrix(XMMatrixPerspectiveFovLH(XMConvertToRadians(m_Fov),
		m_Viewport.Width / m_Viewport.Height, m_Near, m_Far))
{
}

Camera::Camera(
	const ComponentDesc& componentDesc,
	const float& near_, const float& far_, const float& fov) :
	Component(componentDesc, UPDATE, false),
	m_ViewMatrix(
		XMMatrixLookAtLH(
			XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f),		// どの方向を見ているか(方向ベクトル)
			XMVectorSet(								// どの場所にカメラがあるか
				GetTransform().lock()->position().x,
				GetTransform().lock()->position().y,
				GetTransform().lock()->position().z,
				0.0f),
			XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f))),		// カメラの上向き方向
	m_Near(near_),
	m_Far(far_),
	m_Fov(fov)
{
	GetClientRect(Window::g_hWnd, &m_Rect);
	m_Viewport = D3D11_VIEWPORT{ 0.0f, 0.0f, float(m_Rect.right - m_Rect.left), float(m_Rect.bottom - m_Rect.top) };

	m_ProjectionMatrix = XMMatrixPerspectiveFovLH(XMConvertToRadians(m_Fov),
		m_Viewport.Width / m_Viewport.Height, m_Near, m_Far);
}

void Camera::Update()
{
	// ビュー行列を求める(まだ逆行列をしてない)
	Matrix4x4 viewMatrix = Matrix4x4::translate(GetTransform().lock()->position()) * Matrix4x4::rotate(GetTransform().lock()->rotation());
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
		m_Viewport.Width / m_Viewport.Height, m_Near, m_Far);
}

D3D11_VIEWPORT  Camera::GetViewport() const
{
	return m_Viewport;
}

DirectX::XMMATRIX Camera::GetViewMatrix() const
{
	return m_ViewMatrix;
}

DirectX::XMMATRIX Camera::GetProjectionMatrix() const
{
	return m_ProjectionMatrix;
}
