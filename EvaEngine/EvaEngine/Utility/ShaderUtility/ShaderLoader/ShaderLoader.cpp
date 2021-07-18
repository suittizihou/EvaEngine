#include "ShaderLoader.h"
#include "../../../GameSystemBase/DataBase/ShaderDataBase/ShaderDataBase.h"
#include "../ShaderCompiler/ShaderCompiler.h"

using namespace EvaEngine;
using namespace EvaEngine::Internal;

int ShaderLoader::VertexShaderLoad(const std::string& fileName, const std::string& entryPoint)
{
    return ShaderDataBase::Instance().AddVertexShader(ShaderCompiler::CreateVertexShader(fileName, entryPoint));
}

int ShaderLoader::PixelShaderLoad(const std::string& fileName, const std::string& entryPoint)
{
    return ShaderDataBase::Instance().AddPixelShader(ShaderCompiler::CreatePixelShader(fileName, entryPoint));
}

int ShaderLoader::GeometryShaderLoad(const std::string& fileName, const std::string& entryPoint)
{
    return ShaderDataBase::Instance().AddGeometryShader(ShaderCompiler::CreateGeometryShader(fileName, entryPoint));
}

int ShaderLoader::ComputeShaderLoad(const std::string& fileName, const std::string& entryPoint)
{
    return ShaderDataBase::Instance().AddComputeShader(ShaderCompiler::CreateComputeShader(fileName, entryPoint));
}

int ShaderLoader::HullShaderLoad(const std::string& fileName, const std::string& entryPoint)
{
    return ShaderDataBase::Instance().AddHullShader(ShaderCompiler::CreateHullShader(fileName, entryPoint));
}

int ShaderLoader::DomainShaderLoad(const std::string& fileName, const std::string& entryPoint)
{
    return ShaderDataBase::Instance().AddDomainShader(ShaderCompiler::CreateDomainShader(fileName, entryPoint));
}
