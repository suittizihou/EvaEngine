#pragma warning(disable : 4996)

#include "ShaderCompiler.h"
#include <Windows.h>
#include <locale>
#include "../../../App/DirectX11App/DirectX11App.h"

#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")

using namespace EvaEngine::Internal;

ID3D11VertexShader* ShaderCompiler::CreateVertexShader(const std::string& fileName, const std::string& entrypath, bool error)
{
    ID3D11VertexShader* shader{ nullptr };
    D3DBlob blob{ nullptr };

    HRESULT hr = ShaderErrorCheck(fileName, entrypath, "vs_5_0", &blob, error);

    hr = DirectX11App::g_Device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), NULL, &shader);
    if (FAILED(hr)) {
        DebugLog::LogError("VertexShader Create Failed.");
        return nullptr;
    }

    return shader;
}

ID3D11PixelShader* ShaderCompiler::CreatePixelShader(const std::string& fileName, const std::string& entrypath, bool error)
{
    ID3D11PixelShader* shader{ nullptr };
    D3DBlob blob{ nullptr };

    HRESULT hr = ShaderErrorCheck(fileName, entrypath, "ps_5_0", &blob, error);

    hr = DirectX11App::g_Device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &shader);
    if (FAILED(hr)) {
        DebugLog::LogError("PixelShader Create Failed.");
        return nullptr;
    }

    return shader;
}

ID3D11GeometryShader* ShaderCompiler::CreateGeometryShader(const std::string& fileName, const std::string& entrypath, bool error)
{
    ID3D11GeometryShader* shader{ nullptr };
    D3DBlob blob{ nullptr };

    HRESULT hr = ShaderErrorCheck(fileName, entrypath, "gs_5_0", &blob, error);

    hr = DirectX11App::g_Device->CreateGeometryShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &shader);
    if (FAILED(hr)) {
        DebugLog::LogError("GeometryShader Create Failed.");
        return nullptr;
    }

    return shader;
}

ID3D11ComputeShader* ShaderCompiler::CreateComputeShader(const std::string& fileName, const std::string& entrypath, bool error)
{
    ID3D11ComputeShader* shader{ nullptr };
    D3DBlob blob{ nullptr };

    HRESULT hr = ShaderErrorCheck(fileName, entrypath, "cs_5_0", &blob, error);

    hr = DirectX11App::g_Device->CreateComputeShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &shader);
    if (FAILED(hr)) {
        DebugLog::LogError("ComputeShader Create Failed.");
        return nullptr;
    }

    return shader;
}

ID3D11HullShader* ShaderCompiler::CreateHullShader(const std::string& fileName, const std::string& entrypath, bool error)
{
    ID3D11HullShader* shader{ nullptr };
    D3DBlob blob{ nullptr };

    HRESULT hr = ShaderErrorCheck(fileName, entrypath, "hs_5_0", &blob, error);

    hr = DirectX11App::g_Device->CreateHullShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &shader);
    if (FAILED(hr)) {
        DebugLog::LogError("HullShader Create Failed.");
        return nullptr;
    }

    return shader;
}

ID3D11DomainShader* ShaderCompiler::CreateDomainShader(const std::string& fileName, const std::string& entrypath, bool error)
{
    ID3D11DomainShader* shader{ nullptr };
    D3DBlob blob{ nullptr };

    HRESULT hr = ShaderErrorCheck(fileName, entrypath, "ds_5_0", &blob, error);

    hr = DirectX11App::g_Device->CreateDomainShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &shader);
    if (FAILED(hr)) {
        DebugLog::LogError("DomainShader Create Failed.");
        return nullptr;
    }

    return shader;
}

ID3D11InputLayout* ShaderCompiler::CreateVertexLayout(D3D11_INPUT_ELEMENT_DESC* layout, UINT elemNum, const std::string& fileName, const std::string& entryPath)
{
    ID3D11InputLayout* vertexLayout;
    D3DBlob blob{ nullptr };

    HRESULT hr = InputLayoutErrorCheck(fileName, entryPath, "vs_5_0", &blob);
    
    hr = DirectX11App::g_Device->CreateInputLayout(layout, elemNum, blob->GetBufferPointer(), blob->GetBufferSize(), &vertexLayout);
    if (FAILED(hr)) {
        DebugLog::LogError("Input Layout Create Failed.");
        return nullptr;
    }

    return vertexLayout;
}

HRESULT ShaderCompiler::ShaderErrorCheck(const std::string& fileName, const std::string& entryPath, const LPCSTR& pTarget, ID3DBlob** blob, bool error)
{
#if defined(_DEBUG)
    // �O���t�B�b�N�f�o�b�O�c�[���ɂ��V�F�[�_�[�̃f�o�b�O��L���ɂ���
    UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
    UINT compileFlags = 0;
#endif
    wchar_t ws[512];

    setlocale(LC_CTYPE, "jpn");
    mbstowcs(ws, fileName.c_str(), 512);
    D3DBlob errorBlob{ nullptr };
    HRESULT hr = D3DCompileFromFile(ws, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPath.c_str(), pTarget, compileFlags, 0, blob, &errorBlob);

    // �G���[�`�F�b�N
    if (FAILED(hr)) {
        if (error) {
            // �G���[���b�Z�[�W���o��
            if (errorBlob != nullptr && error) {
                DebugLog::LogError((char*)errorBlob->GetBufferPointer());
                return hr;
            }
        }
        else {
            std::string er = (char*)errorBlob->GetBufferPointer();
            if (er.find("entrypoint not found") == std::string::npos)
                DebugLog::LogError((char*)errorBlob->GetBufferPointer());

            DebugLog::LogError(fileName + "(" + entryPath + ") is Not found");
            return hr;
        }
    }

    return hr;
}

HRESULT ShaderCompiler::InputLayoutErrorCheck(const std::string& fileName, const std::string& entryPath, const LPCSTR& pTarget, ID3DBlob** blob)
{
#if defined(_DEBUG)
    // �O���t�B�b�N�f�o�b�O�c�[���ɂ��V�F�[�_�[�̃f�o�b�O��L���ɂ���
    UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
    UINT compileFlags = 0;
#endif
    wchar_t ws[512];

    setlocale(LC_CTYPE, "jpn");
    mbstowcs(ws, fileName.c_str(), 512);
    D3DBlob errorBlob{ nullptr };
    HRESULT hr = D3DCompileFromFile(ws, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPath.c_str(), pTarget, compileFlags, 0, blob, &errorBlob);

    // �G���[�`�F�b�N
    if (FAILED(hr)) {
        // �G���[���b�Z�[�W���o��
        if (errorBlob != nullptr) {
            DebugLog::LogError((char*)errorBlob->GetBufferPointer());
            return hr;
        }
    }

    return hr;
}
