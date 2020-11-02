#pragma once
#include "../ShaderCompiler/ShaderCompiler.h"

class Shader {
public:
	// 頂点シェーダーをセット
	void SetVertexShader(const std::string& filePath, const std::string& entryPoint = "vsMain");
	// ピクセルシェーダーをセット
	void SetPixelShader(const std::string& filePath, const std::string& entryPoint = "psMain");
	// ジオメトリシェーダーをセット
	void SetGeometryShader(const std::string& filePath, const std::string& entryPoint = "gsMain");
	// コンピュートシェーダーをセット
	void SetComputeShader(const std::string& filePath, const std::string& entryPoint = "csMain");
	// ハルシェーダーをセット
	void SetHullShader(const std::string& filePath, const std::string& entryPoint = "hsMain");
	// ドメインシェーダーをセット
	void SetDomainShader(const std::string& filePath, const std::string& entryPoint = "dsMain");

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