#include "Shader.h"
#include "../../../GameSystemBase/DataBase/ShaderDataBase/ShaderDataBase.h"

void Shader::SetVertexShader(const int shaderHandle)
{
	m_VertexShader.Attach(ShaderDataBase::Instance().GetVertexShader(shaderHandle));
}

void Shader::SetPixelShader(const int shaderHandle)
{
	m_PixelShader.Attach(ShaderDataBase::Instance().GetPixelShader(shaderHandle));
}

void Shader::SetGeometryShader(const int shaderHandle)
{
	m_GeometryShader.Attach(ShaderDataBase::Instance().GetGeometryShader(shaderHandle));
}

void Shader::SetComputeShader(const int shaderHandle)
{
	m_ComputeShader.Attach(ShaderDataBase::Instance().GetComputeShader(shaderHandle));
}

void Shader::SetHullShader(const int shaderHandle)
{
	m_HullShader.Attach(ShaderDataBase::Instance().GetHullShader(shaderHandle));
}

void Shader::SetDomainShader(const int shaderHandle)
{
	m_DomainShader.Attach(ShaderDataBase::Instance().GetDomainShader(shaderHandle));
}

VertexShader Shader::GetVertexShader()
{
	return m_VertexShader;
}

PixelShader Shader::GetPixelShader()
{
	return m_PixelShader;
}

GeometryShader Shader::GetGeometryShader()
{
	return m_GeometryShader;
}

ComputeShader Shader::GetComputeShader()
{
	return m_ComputeShader;
}

HullShader Shader::GetHullShader()
{
	return m_HullShader;
}

DomainShader Shader::GetDomainShader()
{
	return m_DomainShader;
}
