#include "Shader.h"
#include "../../../GameSystemBase/DataBase/ShaderDataBase/ShaderDataBase.h"

using namespace EvaEngine;
using namespace EvaEngine::Internal;

EvaEngine::Shader::~Shader()
{
	//AllRelease();
}

void Shader::SetVertexShader(const GUID& shaderHandle)
{
	m_VertexShader = ShaderDataBase::Instance().GetVertexShader(shaderHandle);
}

void EvaEngine::Shader::SetVertexShader(const VertexShader& shader)
{
	m_VertexShader = shader;
}

void Shader::SetPixelShader(const GUID& shaderHandle)
{
	m_PixelShader = ShaderDataBase::Instance().GetPixelShader(shaderHandle);
}

void EvaEngine::Shader::SetPixelShader(const PixelShader& shader)
{
	m_PixelShader = shader;
}

void Shader::SetGeometryShader(const GUID& shaderHandle)
{
	m_GeometryShader = ShaderDataBase::Instance().GetGeometryShader(shaderHandle);
}

void EvaEngine::Shader::SetGeometryShader(const GeometryShader& shader)
{
	m_GeometryShader = shader;
}

void Shader::SetComputeShader(const GUID& shaderHandle)
{
	m_ComputeShader = ShaderDataBase::Instance().GetComputeShader(shaderHandle);
}

void EvaEngine::Shader::SetComputeShader(const ComputeShader& shader)
{
	m_ComputeShader = shader;
}

void Shader::SetHullShader(const GUID& shaderHandle)
{
	m_HullShader = ShaderDataBase::Instance().GetHullShader(shaderHandle);
}

void EvaEngine::Shader::SetHullShader(const HullShader& shader)
{
	m_HullShader = shader;
}

void Shader::SetDomainShader(const GUID& shaderHandle)
{
	m_DomainShader = ShaderDataBase::Instance().GetDomainShader(shaderHandle);
}

void EvaEngine::Shader::SetDomainShader(const DomainShader& shader)
{
	m_DomainShader = shader;
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

//void EvaEngine::Shader::AllRelease()
//{
//	if (m_VertexShader != nullptr) {
//		m_VertexShader->Release();
//		m_VertexShader = nullptr;
//	}
//
//	if (m_PixelShader != nullptr) {
//		m_PixelShader->Release();
//		m_PixelShader = nullptr;
//	}
//
//
//	if (m_GeometryShader != nullptr) {
//		m_GeometryShader->Release();
//		m_GeometryShader = nullptr;
//	}
//
//	if (m_ComputeShader != nullptr) {
//		m_ComputeShader->Release();
//		m_ComputeShader = nullptr;
//	}
//
//	if (m_HullShader != nullptr) {
//		m_HullShader->Release();
//		m_HullShader = nullptr;
//	}
//
//	if (m_DomainShader != nullptr) {
//		m_DomainShader->Release();
//		m_DomainShader = nullptr;
//	}
//}
