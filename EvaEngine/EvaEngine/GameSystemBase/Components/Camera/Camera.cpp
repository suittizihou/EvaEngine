#include "Camera.h"
#include "../../../Setting/Window/Window.h"
#include "../../Base/GameObject/GameObject.h"
#include "../Transform/Transform.h"
#include "../../../Utility/Texture/RenderTexture/RenderTexture.h"
#include "../../Manager/SceneManager/SceneManager.h"
#include "../../../App/DirectX11App/DirectX11App.h"

using namespace DirectX;
using namespace EvaEngine;
using namespace FunctionMask;

std::unordered_map<std::string, std::vector<std::weak_ptr<EvaEngine::Camera>>> EvaEngine::Camera::m_Cameras;

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
	for (auto& camera : m_Cameras) {
		for (int i = 0; i < camera.second.size(); ++i) {
			if (camera.second[i].expired()) {
				// ���������Ɩ����̕������N�����Ɠ���ւ�
				std::iter_swap(camera.second.begin() + i, camera.second.end() - 1);
				camera.second.pop_back();
				return;
			}
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
	m_Cameras[this->GetSceneName()].push_back(weak_from_this());
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
		static_cast<FLOAT>(width),		// �E�B���h�E�̉���
		static_cast<FLOAT>(height),		// �E�B���h�E�̏c��
		0.0f,							// �ŏ��[�x
		1.0f							// �ő�[�x
	};
}

void EvaEngine::Camera::SetBeginSettings(ID3D11DeviceContext* command) const
{
	// �r���[�|�[�g�̃Z�b�g�A�b�v
	command->RSSetViewports(1, &m_Viewport);

	targetTexture->SetRenderTarget(clearColor);

	auto cameraPos = GetTransform().lock()->position();
	Internal::DirectX11App::g_ConstantBufferData.cameraPos = cameraPos;

	// �r���[�s��
	Internal::DirectX11App::g_ConstantBufferData.view = GetViewMatrix().transpose();
	// �v���W�F�N�V�����s��
	Internal::DirectX11App::g_ConstantBufferData.projection = GetProjectionMatrix().transpose();
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
	return XMMatrixInverse(nullptr, (rotateMatrix * positionMatrix));
}

DirectX::XMMATRIX EvaEngine::Camera::CreateProjectionMatrix(const D3D11_VIEWPORT& viewPort, const float& near, const float& far, const float& fovDegree)
{
	return XMMatrixPerspectiveFovLH(XMConvertToRadians(fovDegree),
			viewPort.Width / viewPort.Height, near, far);
}

std::weak_ptr<EvaEngine::Camera> EvaEngine::Camera::GetMainCamera()
{
	auto currentSceneCameras = m_Cameras[SceneManager::GetCurrentSceneName()];
	for (int i = 0; i < currentSceneCameras.size(); ++i) {
		if (currentSceneCameras[i].lock()->GetGameObject().lock()->GetTag() == "Main Camera") {
			return currentSceneCameras[i];
		}
	}

	// ������Ȃ���������weak_ptr��Ԃ�
	return std::weak_ptr<Camera>();
}

std::vector<std::weak_ptr<EvaEngine::Camera>> EvaEngine::Camera::GetAllCamera()
{
	return m_Cameras[SceneManager::GetCurrentSceneName()];
}

std::vector<std::weak_ptr<Camera>> EvaEngine::Camera::GetAllCamera(const std::string& sceneName)
{
	if (m_Cameras.count(sceneName) == 0) return std::vector<std::weak_ptr<Camera>>();
	return m_Cameras[sceneName];
}

void EvaEngine::Camera::AllDeleteCamera()
{
	for (auto& cameras : m_Cameras)
	{
		for (auto& camera : cameras.second) {
			camera.lock()->targetTexture->Release();
		}
	}
}
