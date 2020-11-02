#include "Shader.h"
#include "../../../GameSystemBase/DataBase/ShaderDataBase/ShaderDataBase.h"

void Shader::SetVertexShader(const int shaderHandle)
{
	m_VertexShader.Attach(ShaderDataBase::Instance().GetVertexShader(shaderHandle).Get());
}

void Shader::SetPixelShader(const int shaderHandle)
{
	m_PixelShader.Attach(ShaderDataBase::Instance().GetPixelShader(shaderHandle).Get());
}

void Shader::SetGeometryShader(const int shaderHandle)
{
	m_GeometryShader.Attach(ShaderDataBase::Instance().GetGeometryShader(shaderHandle).Get());
}

void Shader::SetComputeShader(const int shaderHandle)
{
	m_ComputeShader.Attach(ShaderDataBase::Instance().GetComputeShader(shaderHandle).Get());
	
}

void Shader::SetHullShader(const int shaderHandle)
{
	m_HullShader.Attach(ShaderDataBase::Instance().GetHullShader(shaderHandle).Get());
}

void Shader::SetDomainShader(const int shaderHandle)
{
	m_DomainShader.Attach(ShaderDataBase::Instance().GetDomainShader(shaderHandle).Get());
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
