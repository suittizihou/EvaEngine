#include "Material.h"

void EvaEngine::Material::Release()
{
	if (g_Texture != nullptr) g_Texture->Release(); g_Texture = nullptr;
}