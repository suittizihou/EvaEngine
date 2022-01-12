#include "Texture.h"
#include "../../Math/Mathf/Mathf.h"
#include "../../../App/DirectX11App/DirectX11App.h"

using namespace EvaEngine;

EvaEngine::Texture::Texture(const UINT width, const UINT height) : texelSize{ width , height } {
}

EvaEngine::Texture::~Texture()
{
	Release();
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

ID3D11ShaderResourceView* EvaEngine::Texture::GetD3DShaderResrouceView() const
{
	return m_ShaderResourceView;
}

ID3D11SamplerState* EvaEngine::Texture::GetD3DSamplerState() const
{
	return m_SamplerState;
}

void EvaEngine::Texture::Release()
{
	if (m_Texture != nullptr) {
		m_Texture->Release();
		m_Texture = nullptr;
	}
	if (m_ShaderResourceView != nullptr) {
		m_ShaderResourceView->Release();
		m_ShaderResourceView = nullptr;
	}
	if (m_SamplerState != nullptr)
	{
		m_SamplerState->Release();
		m_SamplerState = nullptr;
	}
}
