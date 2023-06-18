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

void ShaderDataBase::AddVertexShader(const VertexShader& vertexShader, GUID* guid)
{
    if (GUIDCreate(guid, "VertexShader")) return;
    m_VertexShaders[*guid] = vertexShader;
}

void ShaderDataBase::AddPixelShader(const PixelShader& pixelShader, GUID* guid)
{
    if (GUIDCreate(guid, "PixelShader")) return;
    m_PixelShaders[*guid] = pixelShader;
}

void ShaderDataBase::AddGeometryShader(const GeometryShader& geometryShader, GUID* guid)
{
    if (GUIDCreate(guid, "GeometryShader")) return;
    m_GeometryShaders[*guid] = geometryShader;
}

void ShaderDataBase::AddComputeShader(const ComputeShader& computeShader, GUID* guid)
{
    if (GUIDCreate(guid, "ComputeShader")) return;
    m_ComputeShaders[*guid] = computeShader;
}

void ShaderDataBase::AddHullShader(const HullShader& hullShader, GUID* guid)
{
    if (GUIDCreate(guid, "HullShader")) return;
    m_HullShaders[*guid] = hullShader;
}

void ShaderDataBase::AddDomainShader(const DomainShader& domainShader, GUID* guid)
{
    if (GUIDCreate(guid, "DomainShader")) return;
    m_DomainShaders[*guid] = domainShader;
}

VertexShader ShaderDataBase::GetDefaultVertexShader()
{
    return m_DefaultVertexShader;
}

PixelShader ShaderDataBase::GetDefaultPixelShader()
{
    return m_DefaultPixelShader;
}

VertexShader ShaderDataBase::GetVertexShader(const GUID& shaderHandle)
{
    return m_VertexShaders[shaderHandle];
}

PixelShader ShaderDataBase::GetPixelShader(const GUID& shaderHandle)
{
    return m_PixelShaders[shaderHandle];
}

GeometryShader ShaderDataBase::GetGeometryShader(const GUID& shaderHandle)
{
    return m_GeometryShaders[shaderHandle];
}

ComputeShader ShaderDataBase::GetComputeShader(const GUID& shaderHandle)
{
    return m_ComputeShaders[shaderHandle];
}

HullShader ShaderDataBase::GetHullShader(const GUID& shaderHandle)
{
    return m_HullShaders[shaderHandle];
}

DomainShader ShaderDataBase::GetDomainShader(const GUID& shaderHandle)
{
    return m_DomainShaders[shaderHandle];
}

void ShaderDataBase::DeleteVertexShader(const GUID& shaderHandle)
{
    m_VertexShaders[shaderHandle].m_pShader->Release();
    m_VertexShaders[shaderHandle].m_pShader = nullptr;
    m_VertexShaders[shaderHandle].m_pShaderCode->Release();
    m_VertexShaders[shaderHandle].m_pShaderCode = nullptr;
    m_VertexShaders[shaderHandle].m_pInputLayout->Release();
    m_VertexShaders[shaderHandle].m_pInputLayout = nullptr;
    m_VertexShaders.erase(shaderHandle);
}

void ShaderDataBase::DeletePixelShader(const GUID& shaderHandle)
{
    m_PixelShaders[shaderHandle].m_pShader->Release();
    m_PixelShaders[shaderHandle].m_pShader = nullptr;
    m_PixelShaders[shaderHandle].m_pShaderCode->Release();
    m_PixelShaders[shaderHandle].m_pShaderCode = nullptr;
    m_PixelShaders.erase(shaderHandle);
}

void ShaderDataBase::DeleteGeometryShader(const GUID& shaderHandle)
{
    m_GeometryShaders[shaderHandle].m_pShader->Release();
    m_GeometryShaders[shaderHandle].m_pShader = nullptr;
    m_GeometryShaders[shaderHandle].m_pShaderCode->Release();
    m_GeometryShaders[shaderHandle].m_pShaderCode = nullptr;
    m_GeometryShaders.erase(shaderHandle);
}

void ShaderDataBase::DeleteComputeShader(const GUID& shaderHandle)
{
    m_ComputeShaders[shaderHandle].m_pShader->Release();
    m_ComputeShaders[shaderHandle].m_pShader = nullptr;
    m_ComputeShaders[shaderHandle].m_pShaderCode->Release();
    m_ComputeShaders[shaderHandle].m_pShaderCode = nullptr;
    m_ComputeShaders.erase(shaderHandle);
}

void ShaderDataBase::DeleteHullShader(const GUID& shaderHandle)
{
    m_HullShaders[shaderHandle].m_pShader->Release();
    m_HullShaders[shaderHandle].m_pShader = nullptr;
    m_HullShaders[shaderHandle].m_pShaderCode->Release();
    m_HullShaders[shaderHandle].m_pShaderCode = nullptr;
    m_HullShaders.erase(shaderHandle);
}

void ShaderDataBase::DeleteDomainShader(const GUID& shaderHandle)
{
    m_DomainShaders[shaderHandle].m_pShader->Release();
    m_DomainShaders[shaderHandle].m_pShader = nullptr;
    m_DomainShaders[shaderHandle].m_pShaderCode->Release();
    m_DomainShaders[shaderHandle].m_pShaderCode = nullptr;
    m_DomainShaders.erase(shaderHandle);
}

void ShaderDataBase::AllDeleteShader()
{
    // �f�t�H���g�V�F�[�_�[�̉��
    if (m_DefaultVertexShader.m_pShader != nullptr) { m_DefaultVertexShader.m_pShader->Release(); m_DefaultVertexShader.m_pShader = nullptr; }
    if (m_DefaultVertexShader.m_pShaderCode != nullptr) { m_DefaultVertexShader.m_pShaderCode->Release(); m_DefaultVertexShader.m_pShaderCode = nullptr; }
    if (m_DefaultVertexShader.m_pInputLayout != nullptr) { m_DefaultVertexShader.m_pInputLayout->Release(); m_DefaultVertexShader.m_pInputLayout = nullptr; }
    if (m_DefaultPixelShader.m_pShader != nullptr) { m_DefaultPixelShader.m_pShader->Release(); m_DefaultPixelShader.m_pShader = nullptr; }
    if (m_DefaultPixelShader.m_pShaderCode != nullptr) { m_DefaultPixelShader.m_pShaderCode->Release(); m_DefaultPixelShader.m_pShaderCode = nullptr; }

	// ���_�V�F�[�_�[�̉��
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

	// �s�N�Z���V�F�[�_�[�̉��
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

	// �W�I���g���V�F�[�_�[�̉��
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

	// �R���s���[�g�V�F�[�_�[�̉��
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

	// �n���V�F�[�_�[�̉��
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

	// �h���C���V�F�[�_�[�̉��
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

bool EvaEngine::Internal::ShaderDataBase::GUIDCreate(GUID* guid, const std::string& shaderType)
{
    return GUIDUtility::Create(guid, "ShaderDataBase�ɂ�" + shaderType + "��GUID�����Ɏ��s���܂����B");
}
