#include "Camera.h"
#include "../../../Setting/Window/Window.h"
#include "../../Base/GameObject/GameObject.h"
#include "../Transform/Transform.h"
#include "../../../Utility/Texture/RenderTexture/RenderTexture.h"

using namespace DirectX;
using namespace EvaEngine;
using namespace FunctionMask;

std::vector<std::weak_ptr<EvaEngine::Camera>> EvaEngine::Camera::m_Cameras{};

EvaEngine::Camera::Camera(
	const D3D11_VIEWPORT& viewPort,
	const float& near,
	const float& far,
	const float& fov) :
	Component(UPDATE, false),
	m_Near(near),
	m_Far(far),
	m_Fov(fov),
	m_Viewport(viewPort),
	m_ProjectionMatrix(CreateProjectionMatrix(viewPort, near, far, fov))
{
	Init();
}

EvaEngine::Camera::Camera(
	const float& near, const float& far, const float& fov) :
	Component(UPDATE, false),
	m_Near(near),
	m_Far(far),
	m_Fov(fov),
	m_Viewport(EvaEngine::Internal::Window::GetViewport())
{
	m_ProjectionMatrix = CreateProjectionMatrix(m_Viewport, near, far, fov);
	Init();
}

EvaEngine::Camera::~Camera()
{
	// �Q�Ɛ悪null�ɂȂ��Ă���̂�����
	for (int i = 0; i < m_Cameras.size(); ++i) {
		if (m_Cameras[i].expired()) {
			// ���������Ɩ����̕������N�����Ɠ���ւ�
			std::iter_swap(m_Cameras.begin() + i, m_Cameras.end() - 1);
			m_Cameras.pop_back();
			return;
		}
	}
}

void EvaEngine::Camera::Init()
{
	targetTexture = std::make_shared<RenderTexture>(m_Viewport.Width, m_Viewport.Height);
	targetTexture->Create();
}

void EvaEngine::Camera::Awake()
{
	m_Cameras.push_back(weak_from_this());
	m_ViewMatrix = CreateViewMatrix(GetTransform());
}

void EvaEngine::Camera::Update()
{
	// �r���[�s����쐬���ݒ�
	m_ViewMatrix = CreateViewMatrix(GetTransform());

	// ������̍쐬
	m_ProjectionMatrix = CreateProjectionMatrix(m_Viewport, m_Near, m_Far, m_Fov);
}

void EvaEngine::Camera::SetViewport(const UINT width, const UINT height)
{
	m_Viewport = D3D11_VIEWPORT
	{
		static_cast<FLOAT>(0),			// �E�B���h�E�̍��[�̍��W
		static_cast<FLOAT>(0),			// �E�B���h�E�̏�[�̍��W
		static_cast<FLOAT>(width - 0),	// �E�B���h�E�̉���
		static_cast<FLOAT>(height - 0),	// �E�B���h�E�̏c��
		0.0f,							// �ŏ��[�x
		1.0f							// �ő�[�x
	};
}

void EvaEngine::Camera::SetRenderTarget() const
{
	targetTexture->SetRenderTarget(clearColor);
}

D3D11_VIEWPORT EvaEngine::Camera::GetViewport() const
{
	return m_Viewport;
}

XMMATRIX EvaEngine::Camera::GetViewMatrixDxMath() const
{
	return m_ViewMatrix;
}

EvaEngine::Matrix4x4 EvaEngine::Camera::GetViewMatrix() const
{
	return Matrix4x4::to_Matrix4x4(m_ViewMatrix);
}

XMMATRIX EvaEngine::Camera::GetProjectionMatrixDxMath() const
{
	return m_ProjectionMatrix;
}

EvaEngine::Matrix4x4 EvaEngine::Camera::GetProjectionMatrix() const
{
	return Matrix4x4::to_Matrix4x4(m_ProjectionMatrix);
}

XMMATRIX EvaEngine::Camera::CreateViewMatrix(const std::weak_ptr<Transform>& transform)
{
	return CreateViewMatrix(Matrix4x4::rotate(transform.lock()->rotation()), Matrix4x4::translate(transform.lock()->position()));
}

DirectX::XMMATRIX EvaEngine::Camera::CreateViewMatrix(const Matrix4x4& rotateMatrix, const Matrix4x4& positionMatrix)
{
	// �r���[�s����t�s��ɂ��ĕԂ�
	return XMMatrixInverse(nullptr, (rotateMatrix * positionMatrix).to_XMMATRIX());
}

DirectX::XMMATRIX EvaEngine::Camera::CreateProjectionMatrix(const D3D11_VIEWPORT& viewPort, const float& near, const float& far, const float& fovDegree)
{
	return XMMatrixPerspectiveFovLH(XMConvertToRadians(fovDegree),
			viewPort.Width / viewPort.Height, near, far);
}

std::weak_ptr<EvaEngine::Camera> EvaEngine::Camera::GetMainCamera()
{
	for (int i = 0; i < m_Cameras.size(); ++i) {
		if (m_Cameras[i].lock()->GetGameObject().lock()->GetTag() == "Main Camera") {
			return m_Cameras[i];
		}
	}

	// ������Ȃ���������weak_ptr��Ԃ�
	return std::weak_ptr<Camera>();
}

std::vector<std::weak_ptr<EvaEngine::Camera>> EvaEngine::Camera::GetAllCamera()
{
	return m_Cameras;
}

void EvaEngine::Camera::AllDeleteCamera()
{
	for (auto& camera : m_Cameras)
	{
		camera.lock()->targetTexture->Release();
	}
}
