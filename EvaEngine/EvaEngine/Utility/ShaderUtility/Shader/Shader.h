#pragma once
#include "../ShaderCompiler/ShaderCompiler.h"

namespace EvaEngine {
	class Shader {
	public:
		Shader() = default;
		~Shader() = default;

		// 頂点シェーダーをセット
		void SetVertexShader(const int shaderHandle);
		void SetVertexShader(ID3D11VertexShader* shader);
		// ピクセルシェーダーをセット
		void SetPixelShader(const int shaderHandle);
		void SetPixelShader(ID3D11PixelShader* shader);
		// ジオメトリシェーダーをセット
		void SetGeometryShader(const int shaderHandle);
		void SetGeometryShader(ID3D11GeometryShader* shader);
		// コンピュートシェーダーをセット
		void SetComputeShader(const int shaderHandle);
		void SetComputeShader(ID3D11ComputeShader* shader);
		// ハルシェーダーをセット
		void SetHullShader(const int shaderHandle);
		void SetHullShader(ID3D11HullShader* shader);
		// ドメインシェーダーをセット
		void SetDomainShader(const int shaderHandle);
		void SetDomainShader(ID3D11DomainShader* shader);

		// 頂点シェーダーの取得
		ID3D11VertexShader* GetVertexShader();
		// ピクセルシェーダーの取得
		ID3D11PixelShader* GetPixelShader();
		// ジオメトリシェーダーの取得
		ID3D11GeometryShader* GetGeometryShader();
		// コンピュートシェーダーの取得
		ID3D11ComputeShader* GetComputeShader();
		// ハルシェーダーの取得
		ID3D11HullShader* GetHullShader();
		// ドメインシェーダーの取得
		ID3D11DomainShader* GetDomainShader();

	private:
		ID3D11VertexShader* m_VertexShader{ nullptr };
		ID3D11PixelShader* m_PixelShader{ nullptr };
		ID3D11GeometryShader* m_GeometryShader{ nullptr };
		ID3D11ComputeShader* m_ComputeShader{ nullptr };
		ID3D11HullShader* m_HullShader{ nullptr };
		ID3D11DomainShader* m_DomainShader{ nullptr };
	};
}