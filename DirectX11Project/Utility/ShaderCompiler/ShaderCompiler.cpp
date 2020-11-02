#pragma warning(disable : 4996)

#include "ShaderCompiler.h"
#include <Windows.h>
#include <locale>
#include "../../App/DirectX11App/DirectX11App.h"
#include "../../System/DebugLog/DebugLog.h"

VertexShader ShaderCompiler::CreateVertexShader(const std::string& fileName, const std::string& entrypath, bool error)
{
    VertexShader shader{ nullptr };
    D3DBlob blob{ nullptr };

    HRESULT hr = ShaderErrorCheck(fileName, entrypath, "vs_5_0", &blob, error);

    hr = DirectX11App::m_Device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), NULL, &shader);
    if (FAILED(hr)) {
        DebugLog::LogError("VertexShader Create Failed.");
        return nullptr;
    }

    return shader;
}

PixelShader ShaderCompiler::CreatePixelShader(const std::string& fileName, const std::string& entrypath, bool error)
{
    PixelShader shader{ nullptr };
    D3DBlob blob{ nullptr };

    HRESULT hr = ShaderErrorCheck(fileName, entrypath, "ps_5_0", &blob, error);

    hr = DirectX11App::m_Device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &shader);
    if (FAILED(hr)) {
        DebugLog::LogError("PixelShader Create Failed.");
        return nullptr;
    }

    return shader;
}

GeometryShader ShaderCompiler::CreateGeometryShader(const std::string& fileName, const std::string& entrypath, bool error)
{
    GeometryShader shader{ nullptr };
    D3DBlob blob{ nullptr };

    HRESULT hr = ShaderErrorCheck(fileName, entrypath, "gs_5_0", &blob, error);

    hr = DirectX11App::m_Device->CreateGeometryShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &shader);
    if (FAILED(hr)) {
        DebugLog::LogError("GeometryShader Create Failed.");
        return nullptr;
    }

    return shader;
}

ComputeShader ShaderCompiler::CreateComputeShader(const std::string& fileName, const std::string& entrypath, bool error)
{
    ComputeShader shader{ nullptr };
    D3DBlob blob{ nullptr };

    HRESULT hr = ShaderErrorCheck(fileName, entrypath, "cs_5_0", &blob, error);

    hr = DirectX11App::m_Device->CreateComputeShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &shader);
    if (FAILED(hr)) {
        DebugLog::LogError("ComputeShader Create Failed.");
        return nullptr;
    }

    return shader;
}

HullShader ShaderCompiler::CreateHullShader(const std::string& fileName, const std::string& entrypath, bool error)
{
    HullShader shader{ nullptr };
    D3DBlob blob{ nullptr };

    HRESULT hr = ShaderErrorCheck(fileName, entrypath, "hs_5_0", &blob, error);

    hr = DirectX11App::m_Device->CreateHullShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &shader);
    if (FAILED(hr)) {
        DebugLog::LogError("HullShader Create Failed.");
        return nullptr;
    }

    return shader;
}

DomainShader ShaderCompiler::CreateDomainShader(const std::string& fileName, const std::string& entrypath, bool error)
{
    DomainShader shader{ nullptr };
    D3DBlob blob{ nullptr };

    HRESULT hr = ShaderErrorCheck(fileName, entrypath, "ds_5_0", &blob, error);

    hr = DirectX11App::m_Device->CreateDomainShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &shader);
    if (FAILED(hr)) {
        DebugLog::LogError("DomainShader Create Failed.");
        return nullptr;
    }

    return shader;
}

InputLayout ShaderCompiler::CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* layout, UINT elemNum, const std::string& fileName, const std::string& entryPath)
{
    InputLayout vertexLayout;
    D3DBlob blob{ nullptr };

    HRESULT hr = InputLayoutErrorCheck(fileName, entryPath, "vs_5_0", &blob);
    
    hr = DirectX11App::m_Device->CreateInputLayout(layout, elemNum, blob->GetBufferPointer(), blob->GetBufferSize(), &vertexLayout);

    return vertexLayout;
}

HRESULT ShaderCompiler::ShaderErrorCheck(const std::string& fileName, const std::string& entryPath, const LPCSTR& pTarget, ID3DBlob** blob, bool error)
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
    D3DBlob errorBlob{ nullptr };
    HRESULT hr = D3DCompileFromFile(ws, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPath.c_str(), pTarget, compileFlags, 0, blob, &errorBlob);

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

HRESULT ShaderCompiler::InputLayoutErrorCheck(const std::string& fileName, const std::string& entryPath, const LPCSTR& pTarget, ID3DBlob** blob)
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
    D3DBlob errorBlob{ nullptr };
    HRESULT hr = D3DCompileFromFile(ws, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, entryPath.c_str(), pTarget, compileFlags, 0, blob, &errorBlob);

    // エラーチェック
    if (FAILED(hr)) {
        // エラーメッセージを出力
        if (errorBlob != nullptr) {
            DebugLog::LogError((char*)errorBlob->GetBufferPointer());
            return hr;
        }
    }

    return hr;
}
