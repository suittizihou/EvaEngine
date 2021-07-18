#include "Shader.h"
#include "../../../GameSystemBase/DataBase/ShaderDataBase/ShaderDataBase.h"

using namespace EvaEngine;
using namespace EvaEngine::Internal;

void Shader::SetVertexShader(const int shaderHandle)
{
	m_VertexShader = ShaderDataBase::Instance().GetVertexShader(shaderHandle);
}

void EvaEngine::Shader::SetVertexShader(ID3D11VertexShader* shader)
{
	m_VertexShader = shader;
}

void Shader::SetPixelShader(const int shaderHandle)
{
	m_PixelShader = ShaderDataBase::Instance().GetPixelShader(shaderHandle);
}

void EvaEngine::Shader::SetPixelShader(ID3D11PixelShader* shader)
{
	m_PixelShader = shader;
}

void Shader::SetGeometryShader(const int shaderHandle)
{
	m_GeometryShader = ShaderDataBase::Instance().GetGeometryShader(shaderHandle);
}

void EvaEngine::Shader::SetGeometryShader(ID3D11GeometryShader* shader)
{
	m_GeometryShader = shader;
}

void Shader::SetComputeShader(const int shaderHandle)
{
	m_ComputeShader = ShaderDataBase::Instance().GetComputeShader(shaderHandle);
}

void EvaEngine::Shader::SetComputeShader(ID3D11ComputeShader* shader)
{
	m_ComputeShader = shader;
}

void Shader::SetHullShader(const int shaderHandle)
{
	m_HullShader = ShaderDataBase::Instance().GetHullShader(shaderHandle);
}

void EvaEngine::Shader::SetHullShader(ID3D11HullShader* shader)
{
	m_HullShader = shader;
}

void Shader::SetDomainShader(const int shaderHandle)
{
	m_DomainShader = ShaderDataBase::Instance().GetDomainShader(shaderHandle);
}

void EvaEngine::Shader::SetDomainShader(ID3D11DomainShader* shader)
{
	m_DomainShader = shader;
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
