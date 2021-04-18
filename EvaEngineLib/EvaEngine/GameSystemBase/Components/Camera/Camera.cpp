#include "Camera.h"
#include "../../../Setting/Window/Window.h"
#include "../../Base/GameObject/GameObject.h"
#include "../Transform/Transform.h"

using namespace DirectX;
using namespace EvaEngine;
using namespace FunctionMask;

Camera::Camera(
	const D3D11_VIEWPORT& viewPort,
	const float& near,
	const float& far,
	const float& fov) :
	Component(UPDATE, false),
	m_Near(near),
	m_Far(far),
	m_Fov(fov),
	m_ProjectionMatrix(CreateProjectionMatrix(viewPort, near, far, fov))
{
}

Camera::Camera(
	const float& near, const float& far, const float& fov) :
	Component(UPDATE, false),
	m_Near(near),
	m_Far(far),
	m_Fov(fov)
{
	m_ProjectionMatrix = CreateProjectionMatrix(Window::GetViewport(), near, far, fov);
}

void Camera::Awake()
{
	m_ViewMatrix = CreateViewMatrix(GetTransform());
}

void Camera::Update()
{
	// ビュー行列を作成し設定
	m_ViewMatrix = CreateViewMatrix(GetTransform());

	// 視錐台の作成
	m_ProjectionMatrix = CreateProjectionMatrix(Window::GetViewport(), m_Near, m_Far, m_Fov);
}

D3D11_VIEWPORT Camera::GetViewport() const
{
	return Window::GetViewport();
}

XMMATRIX Camera::GetViewMatrix() const
{
	return m_ViewMatrix;
}

XMMATRIX Camera::GetProjectionMatrix() const
{
	return m_ProjectionMatrix;
}

XMMATRIX Camera::CreateViewMatrix(const std::weak_ptr<Transform>& transform)
{
	return CreateViewMatrix(Matrix4x4::rotate(transform.lock()->rotation()), Matrix4x4::translate(transform.lock()->position()));
}

DirectX::XMMATRIX Camera::CreateViewMatrix(const Matrix4x4& rotateMatrix, const Matrix4x4& positionMatrix)
{
	// ビュー行列を求める(まだ逆行列をしてない)
	Matrix4x4 viewMatrix = rotateMatrix * positionMatrix;

	// DirectXMathの行列に変換し逆行列にして返す
	return XMMatrixInverse(nullptr,
		XMMATRIX(
			viewMatrix.m[0][0], viewMatrix.m[0][1], viewMatrix.m[0][2], viewMatrix.m[0][3],
			viewMatrix.m[1][0], viewMatrix.m[1][1], viewMatrix.m[1][2], viewMatrix.m[1][3],
			viewMatrix.m[2][0], viewMatrix.m[2][1], viewMatrix.m[2][2], viewMatrix.m[2][3],
			viewMatrix.m[3][0], viewMatrix.m[3][1], viewMatrix.m[3][2], viewMatrix.m[3][3]));
}

DirectX::XMMATRIX Camera::CreateProjectionMatrix(const D3D11_VIEWPORT& viewPort, const float& near, const float& far, const float& fovDegree)
{
	return XMMatrixPerspectiveFovLH(XMConvertToRadians(fovDegree),
			viewPort.Width / viewPort.Height, near, far);
}
