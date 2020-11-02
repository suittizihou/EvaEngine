#pragma once
#include "../ShaderCompiler/ShaderCompiler.h"

class Shader {
public:
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

	// シェーダーをコンテキストにセット
	void SetShader(D3DContext context);

private:
	VertexShader m_VertexShader{ nullptr };
	PixelShader m_PixelShader{ nullptr };
	GeometryShader m_GeometryShader{ nullptr };
	ComputeShader m_ComputeShader{ nullptr };
	HullShader m_HullShader{ nullptr };
	DomainShader m_DomainShader{ nullptr };
};