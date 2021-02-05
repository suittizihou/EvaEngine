#pragma once
#include "../ShaderCompiler/ShaderCompiler.h"

#include "../../../Define/DLLDefine.h"

EVAENGINE_API class Shader {
public:
	Shader() = default;

	// 頂点シェーダーをセット
	void SetVertexShader(const int shaderHandle);
	// ピクセルシェーダーをセット
	void SetPixelShader(const int shaderHandle);
	// ジオメトリシェーダーをセット
	void SetGeometryShader(const int shaderHandle);
	// コンピュートシェーダーをセット
	void SetComputeShader(const int shaderHandle);
	// ハルシェーダーをセット
	void SetHullShader(const int shaderHandle);
	// ドメインシェーダーをセット
	void SetDomainShader(const int shaderHandle);

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