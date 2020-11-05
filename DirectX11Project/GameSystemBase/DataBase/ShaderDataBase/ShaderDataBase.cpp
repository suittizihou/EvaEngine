#include "ShaderDataBase.h"

int ShaderDataBase::AddVertexShader(ID3D11VertexShader* vertexShader)
{
    m_VertexShaders[m_VertexShaderCount] = vertexShader;
    m_VertexShaderCount += 1;
    return m_VertexShaderCount - 1;
}

int ShaderDataBase::AddPixelShader(ID3D11PixelShader* pixelShader)
{
    m_PixelShaders[m_PixelShaderCount] = pixelShader;
    m_PixelShaderCount += 1;
    return m_PixelShaderCount - 1;
}

int ShaderDataBase::AddGeometryShader(ID3D11GeometryShader* geometryShader)
{
    m_GeometryShaders[m_GeometryShaderCount] = geometryShader;
    m_GeometryShaderCount += 1;
    return m_GeometryShaderCount - 1;
}

int ShaderDataBase::AddComputeShader(ID3D11ComputeShader* computeShader)
{
    m_ComputeShaders[m_ComputeShaderCount] = computeShader;
    m_ComputeShaderCount += 1;
    return m_ComputeShaderCount - 1;
}

int ShaderDataBase::AddHullShader(ID3D11HullShader* hullShader)
{
    m_HullShaders[m_HullShaderCount] = hullShader;
    m_HullShaderCount += 1;
    return m_HullShaderCount - 1;
}

int ShaderDataBase::AddDomainShader(ID3D11DomainShader* domainShader)
{
    m_DomainShaders[m_DomainShaderCount] = domainShader;
    m_DomainShaderCount += 1;
    return m_DomainShaderCount - 1;
}

ID3D11VertexShader* ShaderDataBase::GetVertexShader(const int shaderHandle)
{
    return m_VertexShaders[shaderHandle];
}

ID3D11PixelShader* ShaderDataBase::GetPixelShader(const int shaderHandle)
{
    return m_PixelShaders[shaderHandle];
}

ID3D11GeometryShader* ShaderDataBase::GetGeometryShader(const int shaderHandle)
{
    return m_GeometryShaders[shaderHandle];
}

ID3D11ComputeShader* ShaderDataBase::GetComputeShader(const int shaderHandle)
{
    return m_ComputeShaders[shaderHandle];
}

ID3D11HullShader* ShaderDataBase::GetHullShader(const int shaderHandle)
{
    return m_HullShaders[shaderHandle];
}

ID3D11DomainShader* ShaderDataBase::GetDomainShader(const int shaderHandle)
{
    return m_DomainShaders[shaderHandle];
}

void ShaderDataBase::DeleteVertexShader(const int shaderHandle)
{
    m_VertexShaders[shaderHandle]->Release();
    m_VertexShaders.erase(shaderHandle);
}

void ShaderDataBase::DeletePixelShader(const int shaderHandle)
{
    m_PixelShaders[shaderHandle]->Release();
    m_PixelShaders.erase(shaderHandle);
}

void ShaderDataBase::DeleteGeometryShader(const int shaderHandle)
{
    m_GeometryShaders[shaderHandle]->Release();
    m_GeometryShaders.erase(shaderHandle);
}

void ShaderDataBase::DeleteComputeShader(const int shaderHandle)
{
    m_ComputeShaders[shaderHandle]->Release();
    m_ComputeShaders.erase(shaderHandle);
}

void ShaderDataBase::DeleteHullShader(const int shaderHandle)
{
    m_HullShaders[shaderHandle]->Release();
    m_HullShaders.erase(shaderHandle);
}

void ShaderDataBase::DeleteDomainShader(const int shaderHandle)
{
    m_DomainShaders[shaderHandle]->Release();
    m_DomainShaders.erase(shaderHandle);
}

void ShaderDataBase::DeleteAllShader()
{
	// 頂点シェーダーの解放
	for (const auto& shader : m_VertexShaders) {
		shader.second->Release();
	}

	// ピクセルシェーダーの解放
	for (const auto& shader : m_PixelShaders) {
		shader.second->Release();
	}

	// ジオメトリシェーダーの解放
	for (const auto& shader : m_GeometryShaders) {
		shader.second->Release();
	}

	// コンピュートシェーダーの解放
	for (const auto& shader : m_ComputeShaders) {
		shader.second->Release();
	}

	// ハルシェーダーの解放
	for (const auto& shader : m_HullShaders) {
		shader.second->Release();
	}

	// ドメインシェーダーの解放
	for (const auto& shader : m_DomainShaders) {
		shader.second->Release();
	}
}