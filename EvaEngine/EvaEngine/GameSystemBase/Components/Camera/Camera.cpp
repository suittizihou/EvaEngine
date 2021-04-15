#include "Camera.h"
#include "../../../Setting/Window/Window.h"
#include "../../Base/GameObject/GameObject.h"
#include "../Transform/Transform.h"

using namespace DirectX;
using namespace EvaEngine;
using namespace FunctionMask;

std::vector<std::weak_ptr<Camera>> m_Cameras{};

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
	m_Cameras.push_back(shared_from_this());
}

Camera::Camera(
	const float& near, const float& far, const float& fov) :
	Component(UPDATE, false),
	m_Near(near),
	m_Far(far),
	m_Fov(fov)
{
	m_ProjectionMatrix = CreateProjectionMatrix(Window::GetViewport(), near, far, fov);
	m_Cameras.push_back(shared_from_this());
}

EvaEngine::Camera::~Camera()
{
	// 末尾のコンポーネントＩＤと自分のコンポーネントＩＤが同じなら消してリターン
	if (m_Cameras.end()->lock()->GetComponentID() == GetComponentID()) {
		m_Cameras.pop_back();
		return;
	}

	// 自分と同じコンポーネントＩＤのCameraを検索
	for (int i = 0; i < m_Cameras.size(); ++i) {
		if (m_Cameras[i].lock()->GetComponentID() == GetComponentID()) {
			// 消す部分と末尾の部分をクルっと入れ替え
			std::iter_swap(m_Cameras.begin() + i, m_Cameras.end() - 1);
			m_Cameras.pop_back();
			return;
		}
	}
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

XMMATRIX Camera::GetViewMatrixDxMath() const
{
	return m_ViewMatrix;
}

EvaEngine::Matrix4x4 EvaEngine::Camera::GetViewMatrix() const
{
	return Matrix4x4::to_Matrix4x4(m_ViewMatrix);
}

XMMATRIX Camera::GetProjectionMatrixDxMath() const
{
	return m_ProjectionMatrix;
}

EvaEngine::Matrix4x4 EvaEngine::Camera::GetProjectionMatrix() const
{
	return Matrix4x4::to_Matrix4x4(m_ProjectionMatrix);
}

XMMATRIX Camera::CreateViewMatrix(const std::weak_ptr<Transform>& transform)
{
	return CreateViewMatrix(Matrix4x4::rotate(transform.lock()->rotation()), Matrix4x4::translate(transform.lock()->position()));
}

DirectX::XMMATRIX Camera::CreateViewMatrix(const Matrix4x4& rotateMatrix, const Matrix4x4& positionMatrix)
{
	// ビュー行列を逆行列にして返す
	return XMMatrixInverse(nullptr, (rotateMatrix * positionMatrix).to_XMMATRIX());
}

DirectX::XMMATRIX Camera::CreateProjectionMatrix(const D3D11_VIEWPORT& viewPort, const float& near, const float& far, const float& fovDegree)
{
	return XMMatrixPerspectiveFovLH(XMConvertToRadians(fovDegree),
			viewPort.Width / viewPort.Height, near, far);
}

std::weak_ptr<Camera> EvaEngine::Camera::GetMainCamera()
{
	for (int i = 0; i < m_Cameras.size(); ++i) {
		if (m_Cameras[i].lock()->GetGameObject().lock()->GetTag() == "Main Camera") {
			return m_Cameras[i];
		}
	}

	return std::weak_ptr<Camera>();
}

std::vector<std::weak_ptr<Camera>> EvaEngine::Camera::GetAllCamera()
{
	return m_Cameras;
}
