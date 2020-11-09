#include "ResourceLoad.h"
#include "../ModelUtility/ModelLoaderUtility/ModelLoader/ModelLoader.h"
#include "../ShaderUtility/ShaderLoader/ShaderLoader.h"

void ResourceLoad::Load()
{
	ShaderLoader::Instance().VertexShaderLoad("Shader/VertexShader.hlsl");
	ShaderLoader::Instance().PixelShaderLoad("Shader/PixelShader.hlsl");

	ModelLoader::Instance().Load("Resources/alicia-solid.vrm");
	ModelLoader::Instance().Load("Resources/Box.fbx");
}
