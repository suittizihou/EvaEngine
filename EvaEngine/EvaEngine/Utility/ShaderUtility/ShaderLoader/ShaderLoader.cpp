#include "ShaderLoader.h"
#include "../../../GameSystemBase/DataBase/ShaderDataBase/ShaderDataBase.h"
#include "../ShaderCompiler/ShaderCompiler.h"

using namespace EvaEngine;
using namespace EvaEngine::Internal;

void ShaderLoader::VertexShaderLoad(GUID* guid, const std::string& fileName, const D3D11_INPUT_ELEMENT_DESC* layout, const UINT arraySize, const std::string& entryPoint)
{
    VertexShader shader{};
    ShaderCompiler::CreateVertexShader(&shader, layout, arraySize, fileName, entryPoint);
    ShaderDataBase::Instance().AddVertexShader(shader, guid);
}

void ShaderLoader::PixelShaderLoad(GUID* guid, const std::string& fileName, const std::string& entryPoint)
{
    PixelShader shader{};
    ShaderCompiler::CreatePixelShader(&shader, fileName, entryPoint);
    ShaderDataBase::Instance().AddPixelShader(shader, guid);
}

void ShaderLoader::GeometryShaderLoad(GUID* guid, const std::string& fileName, const std::string& entryPoint)
{
    GeometryShader shader{};
    ShaderCompiler::CreateGeometryShader(&shader, fileName, entryPoint);
    ShaderDataBase::Instance().AddGeometryShader(shader, guid);
}

void ShaderLoader::ComputeShaderLoad(GUID* guid, const std::string& fileName, const std::string& entryPoint)
{
    ComputeShader shader{};
    ShaderCompiler::CreateComputeShader(&shader, fileName, entryPoint);
    ShaderDataBase::Instance().AddComputeShader(shader, guid);
}

void ShaderLoader::HullShaderLoad(GUID* guid, const std::string& fileName, const std::string& entryPoint)
{
    HullShader shader{};
    ShaderCompiler::CreateHullShader(&shader, fileName, entryPoint);
    ShaderDataBase::Instance().AddHullShader(shader, guid);
}

void ShaderLoader::DomainShaderLoad(GUID* guid, const std::string& fileName, const std::string& entryPoint)
{
    DomainShader shader{};
    ShaderCompiler::CreateDomainShader(&shader, fileName, entryPoint);
    ShaderDataBase::Instance().AddDomainShader(shader, guid);
}
