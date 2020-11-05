#include "Shader.h"
#include "../../../GameSystemBase/DataBase/ShaderDataBase/ShaderDataBase.h"

void Shader::SetVertexShader(const int shaderHandle)
{
	m_VertexShader = ShaderDataBase::Instance().GetVertexShader(shaderHandle);
}

void Shader::SetPixelShader(const int shaderHandle)
{
	m_PixelShader = ShaderDataBase::Instance().GetPixelShader(shaderHandle);
}

void Shader::SetGeometryShader(const int shaderHandle)
{
	m_GeometryShader = ShaderDataBase::Instance().GetGeometryShader(shaderHandle);
}

void Shader::SetComputeShader(const int shaderHandle)
{
	m_ComputeShader = ShaderDataBase::Instance().GetComputeShader(shaderHandle);
}

void Shader::SetHullShader(const int shaderHandle)
{
	m_HullShader = ShaderDataBase::Instance().GetHullShader(shaderHandle);
}

void Shader::SetDomainShader(const int shaderHandle)
{
	m_DomainShader = ShaderDataBase::Instance().GetDomainShader(shaderHandle);
}

ID3D11VertexShader* Shader::GetVertexShader()
{
	return m_VertexShader;
}

ID3D11PixelShader* Shader::GetPixelShader()
{
	return m_PixelShader;
}

ID3D11GeometryShader* Shader::GetGeometryShader()
{
	return m_GeometryShader;
}

ID3D11ComputeShader* Shader::GetComputeShader()
{
	return m_ComputeShader;
}

ID3D11HullShader* Shader::GetHullShader()
{
	return m_HullShader;
}

ID3D11DomainShader* Shader::GetDomainShader()
{
	return m_DomainShader;
}
