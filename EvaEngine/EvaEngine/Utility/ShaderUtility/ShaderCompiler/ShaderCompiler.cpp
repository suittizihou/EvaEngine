#pragma warning(disable : 4996)

#include "ShaderCompiler.h"
#include <Windows.h>
#include "../../../App/DirectX11App/DirectX11App.h"
#include "../ShaderBase/ShaderBase.h"

#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")

using namespace EvaEngine::Internal;

HRESULT ShaderCompiler::CreateVertexShader(VertexShader* shader, const D3D11_INPUT_ELEMENT_DESC* layout, const UINT arraySize, const std::string& fileName, const std::string& entrypath, bool error)
{
    HRESULT hr = Compile(fileName, entrypath, "vs_5_0", &shader->m_pShaderCode, error);

    hr = DirectX11App::g_Device->CreateVertexShader(shader->m_pShaderCode->GetBufferPointer(), shader->m_pShaderCode->GetBufferSize(), NULL, &shader->m_pShader);
    if (FAILED(hr)) {
        DebugLog::LogError("VertexShader Create Failed.");
        return hr;
    }

    hr = CreateInputLayout(shader, layout, arraySize);

    return hr;
}

HRESULT ShaderCompiler::CreatePixelShader(PixelShader* shader, const std::string& fileName, const std::string& entrypath, bool error)
{
    HRESULT hr = Compile(fileName, entrypath, "ps_5_0", &shader->m_pShaderCode, error);

    hr = DirectX11App::g_Device->CreatePixelShader(shader->m_pShaderCode->GetBufferPointer(), shader->m_pShaderCode->GetBufferSize(), nullptr, &shader->m_pShader);
    if (FAILED(hr)) {
        DebugLog::LogError("PixelShader Create Failed.");
        return hr;
    }

    return hr;
}

HRESULT ShaderCompiler::CreateGeometryShader(GeometryShader* shader, const std::string& fileName, const std::string& entrypath, bool error)
{
    HRESULT hr = Compile(fileName, entrypath, "gs_5_0", &shader->m_pShaderCode, error);

    hr = DirectX11App::g_Device->CreateGeometryShader(shader->m_pShaderCode->GetBufferPointer(), shader->m_pShaderCode->GetBufferSize(), nullptr, &shader->m_pShader);
    if (FAILED(hr)) {
        DebugLog::LogError("GeometryShader Create Failed.");
        return hr;
    }

    return hr;
}

HRESULT ShaderCompiler::CreateComputeShader(ComputeShader* shader, const std::string& fileName, const std::string& entrypath, bool error)
{
    HRESULT hr = Compile(fileName, entrypath, "cs_5_0", &shader->m_pShaderCode, error);

    hr = DirectX11App::g_Device->CreateComputeShader(shader->m_pShaderCode->GetBufferPointer(), shader->m_pShaderCode->GetBufferSize(), nullptr, &shader->m_pShader);
    if (FAILED(hr)) {
        DebugLog::LogError("ComputeShader Create Failed.");
        return hr;
    }

    return hr;
}

HRESULT ShaderCompiler::CreateHullShader(HullShader* shader, const std::string& fileName, const std::string& entrypath, bool error)
{
    HRESULT hr = Compile(fileName, entrypath, "hs_5_0", &shader->m_pShaderCode, error);

    hr = DirectX11App::g_Device->CreateHullShader(shader->m_pShaderCode->GetBufferPointer(), shader->m_pShaderCode->GetBufferSize(), nullptr, &shader->m_pShader);
    if (FAILED(hr)) {
        DebugLog::LogError("HullShader Create Failed.");
        return hr;
    }

    return hr;
}

HRESULT ShaderCompiler::CreateDomainShader(DomainShader* shader, const std::string& fileName, const std::string& entrypath, bool error)
{
    HRESULT hr = Compile(fileName, entrypath, "ds_5_0", &shader->m_pShaderCode, error);

    hr = DirectX11App::g_Device->CreateDomainShader(shader->m_pShaderCode->GetBufferPointer(), shader->m_pShaderCode->GetBufferSize(), nullptr, &shader->m_pShader);
    if (FAILED(hr)) {
        DebugLog::LogError("DomainShader Create Failed.");
        return hr;
    }

    return hr;
}

HRESULT ShaderCompiler::CreateInputLayout(VertexShader* shader, const D3D11_INPUT_ELEMENT_DESC* layout, const UINT arraySize) {
    HRESULT hr = DirectX11App::g_Device->CreateInputLayout(layout, arraySize, shader->m_pShaderCode->GetBufferPointer(), shader->m_pShaderCode->GetBufferSize(), &shader->m_pInputLayout);
    if (FAILED(hr)) {
        DebugLog::LogError("Input Layout Create Failed.");
        return hr;
    }
    return hr;
};

HRESULT ShaderCompiler::Compile(const std::string& fileName, const std::string& entryPath, const LPCSTR& pTarget, ID3DBlob** ppBlob, bool error)
{
#if defined(_DEBUG)
    // グラフィックデバッグツールによるシェーダーのデバッグを有効にする
    UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
    UINT compileFlags = 0;
#endif
    wchar_t ws[512];

    setlocale(LC_CTYPE, "jpn");
    mbstowcs(ws, fileName.c_str(), 512);
    ID3DBlob* errorBlob;
    HRESULT hr = D3DCompileFromFile(ws, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPath.c_str(), pTarget, compileFlags, 0, ppBlob, &errorBlob);

    // エラーチェック
    if (FAILED(hr)) {
        if (error) {
            // エラーメッセージを出力
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