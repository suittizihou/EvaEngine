#include "Texture.h"

using namespace EvaEngine;


Texture::TextureType EvaEngine::Texture::GetTextureType() const
{
	return textureType;
}

Vector2 Texture::GetTexelSize() const
{
	return texelSize;
}