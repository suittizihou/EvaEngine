#include "Shader.h"

void Shader::SetVertexShader(const std::string& filePath, const std::string& entryPoint)
{
	m_VertexShader.Attach(ShaderCompiler::CreateVertexShader(filePath, entryPoint).Get());
}

void Shader::SetPixelShader(const std::string& filePath, const std::string& entryPoint)
{
	m_PixelShader.Attach(ShaderCompiler::CreatePixelShader(filePath, entryPoint).Get());
}

void Shader::SetGeometryShader(const std::string& filePath, const std::string& entryPoint)
{
	m_GeometryShader.Attach(ShaderCompiler::CreateGeometryShader(filePath, entryPoint).Get());
}

void Shader::SetComputeShader(const std::string& filePath, const std::string& entryPoint)
{
	m_ComputeShader.Attach(ShaderCompiler::CreateComputeShader(filePath, entryPoint).Get());
}

void Shader::SetHullShader(const std::string& filePath, const std::string& entryPoint)
{
	m_HullShader.Attach(ShaderCompiler::CreateHullShader(filePath, entryPoint).Get());
}

void Shader::SetDomainShader(const std::string& filePath, const std::string& entryPoint)
{
	m_DomainShader.Attach(ShaderCompiler::CreateDomainShader(filePath, entryPoint).Get());
}

void Shader::SetShader(D3DContext context)
{
	// それぞれ nullptr でない場合シェーダーをセットする
	if (m_VertexShader != nullptr) context->VSSetShader(m_VertexShader.Get(), nullptr, 0);
	if (m_HullShader != nullptr) context->HSSetShader(m_HullShader.Get(), nullptr, 0);
	if (m_DomainShader != nullptr) context->DSSetShader(m_DomainShader.Get(), nullptr, 0);
	if (m_GeometryShader != nullptr) context->GSSetShader(m_GeometryShader.Get(), nullptr, 0);
	if (m_ComputeShader != nullptr) context->CSSetShader(m_ComputeShader.Get(), nullptr, 0);
	if (m_PixelShader != nullptr) context->PSSetShader(m_PixelShader.Get(), nullptr, 0);
}
