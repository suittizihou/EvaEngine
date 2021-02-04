#include "ResourceLoad.h"
#include "../ModelUtility/ModelLoader/ModelLoader.h"
#include "../ShaderUtility/ShaderLoader/ShaderLoader.h"

void ResourceLoad::Load()
{
	ShaderLoader::VertexShaderLoad("Shader/VertexShader.hlsl");
	ShaderLoader::PixelShaderLoad("Shader/PixelShader.hlsl");

	ModelLoader::Load("Resources/alicia-solid.vrm");
	ModelLoader::Load("Resources/Box.fbx");
	ModelLoader::Load("Resources/Cube.obj");
}
