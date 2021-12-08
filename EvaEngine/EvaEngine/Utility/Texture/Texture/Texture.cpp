#include "Texture.h"
#include "../../Math/Mathf/Mathf.h"
#include "../../../App/DirectX11App/DirectX11App.h"

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

void EvaEngine::Texture::CreateShaderResourceView(const ID3D11Resource& resource, const D3D11_SHADER_RESOURCE_VIEW_DESC& desc)
{
	HRESULT hr = Internal::DirectX11App::g_Device->CreateShaderResourceView(m_Texture, &desc, &m_ShaderResourceView);

	if (FAILED(hr)) DebugLog::LogError(u8"Failed : CreateShaderResourceView in Texture");
}

void EvaEngine::Texture::CreateSamplerState(const D3D11_SAMPLER_DESC& desc)
{
	HRESULT hr = Internal::DirectX11App::g_Device->CreateSamplerState(&desc, &m_SamplerState);

	if (FAILED(hr)) DebugLog::LogError(u8"Failed : CreateSamplerState in Texture");
}

ID3D11ShaderResourceView* EvaEngine::Texture::GetD3DShaderResrouceView() const
{
	return m_ShaderResourceView;
}

ID3D11SamplerState* EvaEngine::Texture::GetD3DSamplerState() const
{
	return m_SamplerState;
}
