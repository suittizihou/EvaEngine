#include "Texture.h"
#include "../../Math/Mathf/Mathf.h"

using namespace EvaEngine;

EvaEngine::Texture::Texture(const UINT width, const UINT height) : texelSize{ width , height } {
}

Texture::TextureType EvaEngine::Texture::GetTextureType() const
{
	return textureType;
}

Vector2 Texture::GetTexelSize() const
{
	return texelSize;
}

Vector2 EvaEngine::Texture::GetAspect() const
{
	int gcd = Mathf::gcd(static_cast<int>(texelSize.x), static_cast<int>(texelSize.y));
	if (gcd == 0) return Vector2();
	return Vector2(texelSize.x / gcd, texelSize.y / gcd);
}
