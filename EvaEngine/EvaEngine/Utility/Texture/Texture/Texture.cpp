#include "Texture.h"
#include "../../Math/Mathf/Mathf.h"
#include "../../../App/DirectX11App/DirectX11App.h"
#include <cmath>

using namespace EvaEngine;

EvaEngine::Texture::Texture(const Vector2Int& texelSize) : Texture(texelSize.x, texelSize.y) {}

EvaEngine::Texture::Texture(const int width, const int height) : texelSize{ std::max(width,0) , std::max(height, 0) } {
}

EvaEngine::Texture::~Texture()
{
	Release();
}

Texture::TextureType EvaEngine::Texture::GetTextureType() const
{
	return textureType;
}

Vector2Int Texture::GetTexelSize() const
{
	return texelSize;
}

Vector2Int EvaEngine::Texture::GetAspect() const
{
	int gcd = Mathf::gcd(static_cast<int>(texelSize.x), static_cast<int>(texelSize.y));
	if (gcd == 0) return Vector2Int();
	return Vector2Int(texelSize.x / gcd, texelSize.y / gcd);
}

ID3D11ShaderResourceView* EvaEngine::Texture::GetD3DShaderResrouceView() const
{
	return m_ShaderResourceView;
}

ID3D11SamplerState* EvaEngine::Texture::GetD3DSamplerState() const
{
	return m_SamplerState;
}

void EvaEngine::Texture::SetD3DResource(ID3D11Resource* resource)
{
	m_Texture = resource;
}

void EvaEngine::Texture::SetD3DShaderResourceView(ID3D11ShaderResourceView* shaderResourceView)
{
	m_ShaderResourceView = shaderResourceView;
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
