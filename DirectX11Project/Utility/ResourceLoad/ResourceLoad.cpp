#include "ResourceLoad.h"
#include "../ModelUtility/ModelLoaderUtility/ModelLoadManager/ModelLoadManager.h"
#include "../ShaderUtility/ShaderLoader/ShaderLoader.h"

void ResourceLoad::Load()
{
	ShaderLoader::Instance().VertexShaderLoad("Shader/VertexShader.hlsl");
	ShaderLoader::Instance().PixelShaderLoad("Shader/PixelShader.hlsl");

	ModelLoadManager::Instance().Load("Resources/alicia-solid.vrm");
	ModelLoadManager::Instance().Load("Resources/Box.fbx");
	ModelLoadManager::Instance().Load("Resources/Cube.obj");
}
