#include "ShaderDataBase.h"

int ShaderDataBase::AddVertexShader(const VertexShader& vertexShader)
{
    m_VertexShaders[m_VertexShaderCount] = vertexShader;
    m_VertexShaderCount += 1;
    return m_VertexShaderCount - 1;
}

int ShaderDataBase::AddPixelShader(const PixelShader& pixelShader)
{
    m_PixelShaders[m_PixelShaderCount] = pixelShader;
    m_PixelShaderCount += 1;
    return m_PixelShaderCount - 1;
}

int ShaderDataBase::AddGeometryShader(const GeometryShader& geometryShader)
{
    m_GeometryShaders[m_GeometryShaderCount] = geometryShader;
    m_GeometryShaderCount += 1;
    return m_GeometryShaderCount - 1;
}

int ShaderDataBase::AddComputeShader(const ComputeShader& computeShader)
{
    m_ComputeShaders[m_ComputeShaderCount] = computeShader;
    m_ComputeShaderCount += 1;
    return m_ComputeShaderCount - 1;
}

int ShaderDataBase::AddHullShader(const HullShader& hullShader)
{
    m_HullShaders[m_HullShaderCount] = hullShader;
    m_HullShaderCount += 1;
    return m_HullShaderCount - 1;
}

int ShaderDataBase::AddDomainShader(const DomainShader& domainShader)
{
    m_DomainShaders[m_DomainShaderCount] = domainShader;
    m_DomainShaderCount += 1;
    return m_DomainShaderCount - 1;
}

VertexShader ShaderDataBase::GetVertexShader(const int shaderHandle)
{
    return m_VertexShaders[shaderHandle];
}

PixelShader ShaderDataBase::GetPixelShader(const int shaderHandle)
{
    return m_PixelShaders[shaderHandle];
}

GeometryShader ShaderDataBase::GetGeometryShader(const int shaderHandle)
{
    return m_GeometryShaders[shaderHandle];
}

ComputeShader ShaderDataBase::GetComputeShader(const int shaderHandle)
{
    return m_ComputeShaders[shaderHandle];
}

HullShader ShaderDataBase::GetHullShader(const int shaderHandle)
{
    return m_HullShaders[shaderHandle];
}

DomainShader ShaderDataBase::GetDomainShader(const int shaderHandle)
{
    return m_DomainShaders[shaderHandle];
}

void ShaderDataBase::DeleteVertexShader(const int shaderHandle)
{
    m_VertexShaders.erase(shaderHandle);
}

void ShaderDataBase::DeletePixelShader(const int shaderHandle)
{
    m_PixelShaders.erase(shaderHandle);
}

void ShaderDataBase::DeleteGeometryShader(const int shaderHandle)
{
    m_GeometryShaders.erase(shaderHandle);
}

void ShaderDataBase::DeleteComputeShader(const int shaderHandle)
{
    m_ComputeShaders.erase(shaderHandle);
}

void ShaderDataBase::DeleteHullShader(const int shaderHandle)
{
    m_HullShaders.erase(shaderHandle);
}

void ShaderDataBase::DeleteDomainShader(const int shaderHandle)
{
    m_DomainShaders.erase(shaderHandle);
}