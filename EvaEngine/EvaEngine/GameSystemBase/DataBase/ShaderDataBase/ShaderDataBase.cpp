#include "ShaderDataBase.h"
#include "../../../Utility/ShaderUtility/ShaderCompiler/ShaderCompiler.h"

using namespace EvaEngine::Internal;

ShaderDataBase::~ShaderDataBase() 
{ 
}

void ShaderDataBase::LoadDefaultShader()
{
    D3D11_INPUT_ELEMENT_DESC elem[] = {
    { "POSITION",   0, DXGI_FORMAT_R32G32B32_FLOAT,     0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "NORMAL",     0, DXGI_FORMAT_R32G32B32_FLOAT,     0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
    { "COLOR",      0, DXGI_FORMAT_R32G32B32A32_FLOAT,  0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
    { "TEXCOORD",   0, DXGI_FORMAT_R32G32_FLOAT,        0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    ShaderCompiler::CreateVertexShader(&m_DefaultVertexShader, elem, ARRAYSIZE(elem), "Shader/VertexShader.hlsl");
    ShaderCompiler::CreatePixelShader(&m_DefaultPixelShader, "Shader/PixelShader.hlsl");
}

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

VertexShader ShaderDataBase::GetDefaultVertexShader()
{
    return m_DefaultVertexShader;
}

PixelShader ShaderDataBase::GetDefaultPixelShader()
{
    return m_DefaultPixelShader;
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
    m_VertexShaders[shaderHandle].m_pShader->Release();
    m_VertexShaders[shaderHandle].m_pShader = nullptr;
    m_VertexShaders[shaderHandle].m_pShaderCode->Release();
    m_VertexShaders[shaderHandle].m_pShaderCode = nullptr;
    m_VertexShaders[shaderHandle].m_pInputLayout->Release();
    m_VertexShaders[shaderHandle].m_pInputLayout = nullptr;
    m_VertexShaders.erase(shaderHandle);
}

void ShaderDataBase::DeletePixelShader(const int shaderHandle)
{
    m_PixelShaders[shaderHandle].m_pShader->Release();
    m_PixelShaders[shaderHandle].m_pShader = nullptr;
    m_PixelShaders[shaderHandle].m_pShaderCode->Release();
    m_PixelShaders[shaderHandle].m_pShaderCode = nullptr;
    m_PixelShaders.erase(shaderHandle);
}

void ShaderDataBase::DeleteGeometryShader(const int shaderHandle)
{
    m_GeometryShaders[shaderHandle].m_pShader->Release();
    m_GeometryShaders[shaderHandle].m_pShader = nullptr;
    m_GeometryShaders[shaderHandle].m_pShaderCode->Release();
    m_GeometryShaders[shaderHandle].m_pShaderCode = nullptr;
    m_GeometryShaders.erase(shaderHandle);
}

void ShaderDataBase::DeleteComputeShader(const int shaderHandle)
{
    m_ComputeShaders[shaderHandle].m_pShader->Release();
    m_ComputeShaders[shaderHandle].m_pShader = nullptr;
    m_ComputeShaders[shaderHandle].m_pShaderCode->Release();
    m_ComputeShaders[shaderHandle].m_pShaderCode = nullptr;
    m_ComputeShaders.erase(shaderHandle);
}

void ShaderDataBase::DeleteHullShader(const int shaderHandle)
{
    m_HullShaders[shaderHandle].m_pShader->Release();
    m_HullShaders[shaderHandle].m_pShader = nullptr;
    m_HullShaders[shaderHandle].m_pShaderCode->Release();
    m_HullShaders[shaderHandle].m_pShaderCode = nullptr;
    m_HullShaders.erase(shaderHandle);
}

void ShaderDataBase::DeleteDomainShader(const int shaderHandle)
{
    m_DomainShaders[shaderHandle].m_pShader->Release();
    m_DomainShaders[shaderHandle].m_pShader = nullptr;
    m_DomainShaders[shaderHandle].m_pShaderCode->Release();
    m_DomainShaders[shaderHandle].m_pShaderCode = nullptr;
    m_DomainShaders.erase(shaderHandle);
}

void ShaderDataBase::AllDeleteShader()
{
    // デフォルトシェーダーの解放
    if (m_DefaultVertexShader.m_pShader != nullptr) { m_DefaultVertexShader.m_pShader->Release(); m_DefaultVertexShader.m_pShader = nullptr; }
    if (m_DefaultVertexShader.m_pShaderCode != nullptr) { m_DefaultVertexShader.m_pShaderCode->Release(); m_DefaultVertexShader.m_pShaderCode = nullptr; }
    if (m_DefaultVertexShader.m_pInputLayout != nullptr) { m_DefaultVertexShader.m_pInputLayout->Release(); m_DefaultVertexShader.m_pInputLayout = nullptr; }
    if (m_DefaultPixelShader.m_pShader != nullptr) { m_DefaultPixelShader.m_pShader->Release(); m_DefaultPixelShader.m_pShader = nullptr; }
    if (m_DefaultPixelShader.m_pShaderCode != nullptr) { m_DefaultPixelShader.m_pShaderCode->Release(); m_DefaultPixelShader.m_pShaderCode = nullptr; }

	// 頂点シェーダーの解放
	for (auto& shader : m_VertexShaders) {
            if (shader.second.m_pShader != nullptr) {
                shader.second.m_pShader->Release();
                shader.second.m_pShader = nullptr;
            }
            if (shader.second.m_pShaderCode != nullptr) {
                shader.second.m_pShaderCode->Release();
                shader.second.m_pShaderCode = nullptr;
            }
            if (shader.second.m_pInputLayout != nullptr) {
                shader.second.m_pInputLayout->Release();
                shader.second.m_pInputLayout = nullptr;
            }
    }
    m_VertexShaders.clear();

	// ピクセルシェーダーの解放
    for (auto& shader : m_PixelShaders) {
        if (shader.second.m_pShader != nullptr) {
            shader.second.m_pShader->Release();
            shader.second.m_pShader = nullptr;
        }
        if (shader.second.m_pShaderCode != nullptr) {
            shader.second.m_pShaderCode->Release();
            shader.second.m_pShaderCode = nullptr;
        }
    }
    m_PixelShaders.clear();

	// ジオメトリシェーダーの解放
	for (auto& shader : m_GeometryShaders) {
        if (shader.second.m_pShader != nullptr) {
            shader.second.m_pShader->Release();
            shader.second.m_pShader = nullptr;
        }
        if (shader.second.m_pShaderCode != nullptr) {
            shader.second.m_pShaderCode->Release();
            shader.second.m_pShaderCode = nullptr;
        }
    }
    m_GeometryShaders.clear();

	// コンピュートシェーダーの解放
	for (auto& shader : m_ComputeShaders) {
        if (shader.second.m_pShader != nullptr) {
            shader.second.m_pShader->Release();
            shader.second.m_pShader = nullptr;
        }
        if (shader.second.m_pShaderCode != nullptr) {
            shader.second.m_pShaderCode->Release();
            shader.second.m_pShaderCode = nullptr;
        }
    }
    m_ComputeShaders.clear();

	// ハルシェーダーの解放
	for (auto& shader : m_HullShaders) {
        if (shader.second.m_pShader != nullptr) {
            shader.second.m_pShader->Release();
            shader.second.m_pShader = nullptr;
        }
        if (shader.second.m_pShaderCode != nullptr) {
            shader.second.m_pShaderCode->Release();
            shader.second.m_pShaderCode = nullptr;
        }
    }
    m_HullShaders.clear();

	// ドメインシェーダーの解放
	for (auto& shader : m_DomainShaders) {
        if (shader.second.m_pShader != nullptr) {
            shader.second.m_pShader->Release();
            shader.second.m_pShader = nullptr;
        }
        if (shader.second.m_pShaderCode != nullptr) {
            shader.second.m_pShaderCode->Release();
            shader.second.m_pShaderCode = nullptr;
        }
    }
    m_DomainShaders.clear();
}