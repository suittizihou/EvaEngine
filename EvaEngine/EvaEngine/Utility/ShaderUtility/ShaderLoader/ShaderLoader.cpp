#include "ShaderLoader.h"
#include "../../../GameSystemBase/DataBase/ShaderDataBase/ShaderDataBase.h"
#include "../ShaderCompiler/ShaderCompiler.h"

using namespace EvaEngine;
using namespace EvaEngine::Internal;

int ShaderLoader::VertexShaderLoad(const std::string& fileName, const D3D11_INPUT_ELEMENT_DESC* layout, const UINT arraySize, const std::string& entryPoint)
{
    VertexShader shader{};
    ShaderCompiler::CreateVertexShader(&shader, layout, arraySize, fileName, entryPoint);
    return ShaderDataBase::Instance().AddVertexShader(shader);
}

int ShaderLoader::PixelShaderLoad(const std::string& fileName, const std::string& entryPoint)
{
    PixelShader shader{};
    ShaderCompiler::CreatePixelShader(&shader, fileName, entryPoint);
    return ShaderDataBase::Instance().AddPixelShader(shader);
}

int ShaderLoader::GeometryShaderLoad(const std::string& fileName, const std::string& entryPoint)
{
    GeometryShader shader{};
    ShaderCompiler::CreateGeometryShader(&shader, fileName, entryPoint);
    return ShaderDataBase::Instance().AddGeometryShader(shader);
}

int ShaderLoader::ComputeShaderLoad(const std::string& fileName, const std::string& entryPoint)
{
    ComputeShader shader{};
    ShaderCompiler::CreateComputeShader(&shader, fileName, entryPoint);
    return ShaderDataBase::Instance().AddComputeShader(shader);
}

int ShaderLoader::HullShaderLoad(const std::string& fileName, const std::string& entryPoint)
{
    HullShader shader{};
    ShaderCompiler::CreateHullShader(&shader, fileName, entryPoint);
    return ShaderDataBase::Instance().AddHullShader(shader);
}

int ShaderLoader::DomainShaderLoad(const std::string& fileName, const std::string& entryPoint)
{
    DomainShader shader{};
    ShaderCompiler::CreateDomainShader(&shader, fileName, entryPoint);
    return ShaderDataBase::Instance().AddDomainShader(shader);
}
