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
		// ビューポートの設定
		void SetViewport(const UINT width, const UINT height);
		// レンダーターゲットを設定
		void SetRenderTarget() const;

		// ビューポートを取得
		D3D11_VIEWPORT  GetViewport() const;
		// ビュー行列を取得
		DirectX::XMMATRIX GetViewMatrixDxMath() const;
		EvaEngine::Matrix4x4 GetViewMatrix() const;
		// プロジェクション行列を取得
		DirectX::XMMATRIX GetProjectionMatrixDxMath() const;
		EvaEngine::Matrix4x4 GetProjectionMatrix() const;

		// ビュー行列を作成
		DirectX::XMMATRIX CreateViewMatrix(const std::weak_ptr<Transform>& transform);
		DirectX::XMMATRIX CreateViewMatrix(const Matrix4x4& rotateMatrix, const Matrix4x4& positionMatrix);
		// プロジェクション行列を作成
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
		// シーンに存在するMain CameraタグのCameraコンポーネントを返す
		static std::weak_ptr<Camera> GetMainCamera();
		// 現在のシーンの全カメラを返す
		static std::vector<std::weak_ptr<Camera>> GetAllCamera();
		// 指定されたシーンの全カメラを返す
		static std::vector<std::weak_ptr<Camera>> GetAllCamera(const std::string& sceneName);
		// 全カメラの解放
		static void AllDeleteCamera();

	private:
		static std::unordered_map<std::string, std::vector<std::weak_ptr<Camera>>> m_Cameras;
	};
}