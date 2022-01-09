#pragma once
#include "../ShaderCompiler/ShaderCompiler.h"
#include "../ShaderBase/ShaderBase.h"

namespace EvaEngine {
	class Shader {
	public:
		Shader() = default;
		~Shader();

		// 頂点シェーダーをセット
		void SetVertexShader(const GUID& shaderHandle);
		void SetVertexShader(const Internal::VertexShader& shader);
		// ピクセルシェーダーをセット
		void SetPixelShader(const GUID& shaderHandle);
		void SetPixelShader(const Internal::PixelShader& shader);
		// ジオメトリシェーダーをセット
		void SetGeometryShader(const GUID& shaderHandle);
		void SetGeometryShader(const Internal::GeometryShader& shader);
		// コンピュートシェーダーをセット
		void SetComputeShader(const GUID& shaderHandle);
		void SetComputeShader(const Internal::ComputeShader& shader);
		// ハルシェーダーをセット
		void SetHullShader(const GUID& shaderHandle);
		void SetHullShader(const Internal::HullShader& shader);
		// ドメインシェーダーをセット
		void SetDomainShader(const GUID& shaderHandle);
		void SetDomainShader(const Internal::DomainShader& shader);

		// 頂点シェーダーの取得
		Internal::VertexShader GetVertexShader();
		// ピクセルシェーダーの取得
		Internal::PixelShader GetPixelShader();
		// ジオメトリシェーダーの取得
		Internal::GeometryShader GetGeometryShader();
		// コンピュートシェーダーの取得
		Internal::ComputeShader GetComputeShader();
		// ハルシェーダーの取得
		Internal::HullShader GetHullShader();
		// ドメインシェーダーの取得
		Internal::DomainShader GetDomainShader();

	private:
		//void AllRelease();

	private:
		Internal::VertexShader m_VertexShader{};
		Internal::PixelShader m_PixelShader{};
		Internal::GeometryShader m_GeometryShader{};
		Internal::ComputeShader m_ComputeShader{};
		Internal::HullShader m_HullShader{};
		Internal::DomainShader m_DomainShader{};
	};
}