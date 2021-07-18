#pragma once

#include <DirectXMath.h>
#include <memory>
#include <vector>
#include "../../../App/DirectX11App/DirectX11App.h"
#include "../../Base/Component/Component.h"

#undef near
#undef far

namespace EvaEngine {

	struct Matrix4x4;

	class Camera : public Component, public std::enable_shared_from_this<Camera>
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

		~Camera();

	public:
		void Awake() override;
		void Update() override;

#if _DEBUG
		void OnGUI() override {}
#endif

	public:
		// �r���[�|�[�g���擾
		D3D11_VIEWPORT  GetViewport() const;
		// �r���[�s����擾
		DirectX::XMMATRIX GetViewMatrixDxMath() const;
		EvaEngine::Matrix4x4 GetViewMatrix() const;
		// �v���W�F�N�V�����s����擾
		DirectX::XMMATRIX GetProjectionMatrixDxMath() const;
		EvaEngine::Matrix4x4 GetProjectionMatrix() const;

		// �r���[�s����쐬
		DirectX::XMMATRIX CreateViewMatrix(const std::weak_ptr<Transform>& transform);
		DirectX::XMMATRIX CreateViewMatrix(const Matrix4x4& rotateMatrix, const Matrix4x4& positionMatrix);
		// �v���W�F�N�V�����s����쐬
		DirectX::XMMATRIX CreateProjectionMatrix(
			const D3D11_VIEWPORT& viewPort,
			const float& near,
			const float& far,
			const float& fovDegree);

	public:
		// �V�[���ɑ��݂���Main Camera�^�O��Camera�R���|�[�l���g��Ԃ�
		static std::weak_ptr<Camera> GetMainCamera();
		// �S�J������Ԃ�
		static std::vector<std::weak_ptr<Camera>> GetAllCamera();

	private:
		DirectX::XMMATRIX m_ViewMatrix{};
		DirectX::XMMATRIX m_ProjectionMatrix{};

		float m_Near{};
		float m_Far{};
		float m_Fov{};

	private:
		static std::vector<std::weak_ptr<Camera>> m_Cameras;
	};
}