#pragma once

#include <DirectXMath.h>
#include <memory>
#include <vector>
#include <unordered_map>
#include "../../../App/DirectX11App/DirectX11App.h"
#include "../../Base/Component/Component.h"
#include "../../../Utility/Math/Color/Color.h"

#undef near
#undef far

namespace EvaEngine {

	struct Matrix4x4;
	class RenderTexture;

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

	protected:
		void Init() override;

	public:
		void Awake() override;
		void Update() override;

#if _DEBUG
		void OnGUI() override {}
#endif

	public:
		// �r���[�|�[�g�̐ݒ�
		void SetViewport(const UINT width, const UINT height);
		// �����_�[�^�[�Q�b�g��ݒ�
		void SetBeginSettings(ID3D11DeviceContext* command) const;

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
		std::shared_ptr<RenderTexture> targetTexture{ nullptr };
		Color clearColor{ 1.0f, 1.0f, 1.0f, 1.0f };

	private:
		D3D11_VIEWPORT m_Viewport{};

	private:
		DirectX::XMMATRIX m_ViewMatrix{};
		DirectX::XMMATRIX m_ProjectionMatrix{};

		float m_Near{};
		float m_Far{};
		float m_Fov{};

	public:
		// �V�[���ɑ��݂���Main Camera�^�O��Camera�R���|�[�l���g��Ԃ�
		static std::weak_ptr<Camera> GetMainCamera();
		// ���݂̃V�[���̑S�J������Ԃ�
		static std::vector<std::weak_ptr<Camera>> GetAllCamera();
		// �w�肳�ꂽ�V�[���̑S�J������Ԃ�
		static std::vector<std::weak_ptr<Camera>> GetAllCamera(const std::string& sceneName);
		// �S�J�����̉��
		static void AllDeleteCamera();

	private:
		static std::unordered_map<std::string, std::vector<std::weak_ptr<Camera>>> m_Cameras;
	};
}