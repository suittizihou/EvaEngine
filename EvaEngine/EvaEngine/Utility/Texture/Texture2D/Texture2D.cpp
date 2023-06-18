#include "Texture2D.h"
#include "../../../App/DirectX11App/DirectX11App.h"

using namespace EvaEngine;
using namespace EvaEngine::Internal;

EvaEngine::Texture2D::Texture2D(const Vector2& texelSize) : Texture2D(texelSize.x, texelSize.y)
{
}

EvaEngine::Texture2D::Texture2D(const Vector2& texelSize, const DXGI_FORMAT& textureFormat) : Texture2D(texelSize.x, texelSize.y, textureFormat)
{
}

EvaEngine::Texture2D::Texture2D(const Vector2& texelSize, const D3D11_TEXTURE2D_DESC& textureDesc) : Texture2D(texelSize.x, texelSize.y, textureDesc)
{
}

EvaEngine::Texture2D::Texture2D(const UINT width, const UINT height) : Texture2D(width, height, DXGI_FORMAT_R8G8B8A8_UNORM)
{
}

EvaEngine::Texture2D::Texture2D(const UINT width, const UINT height, const DXGI_FORMAT& textureFormat) : Texture(width, height)
{
	memset(&m_TextureDesc, 0, sizeof(m_TextureDesc));
	m_TextureDesc.Usage = D3D11_USAGE_DEFAULT;
	m_TextureDesc.Format = textureFormat;
	m_TextureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	m_TextureDesc.Width = width;
	m_TextureDesc.Height = height;
	m_TextureDesc.CPUAccessFlags = 0;
	m_TextureDesc.MipLevels = 1;
	m_TextureDesc.ArraySize = 1;
	m_TextureDesc.SampleDesc.Count = 1;
	m_TextureDesc.SampleDesc.Quality = 0;

	Init();
}

EvaEngine::Texture2D::Texture2D(const UINT width, const UINT height, const D3D11_TEXTURE2D_DESC& textureDesc) : Texture(width, height)
{
	this->m_TextureDesc = textureDesc;
	Init();
}

EvaEngine::Texture2D::~Texture2D()
{
}

void EvaEngine::Texture2D::Init()
{
	textureType = TextureType::Tex2D;
}

void EvaEngine::Texture2D::Create()
{
	auto format = DXGI_FORMAT_R8G8B8A8_UNORM;
	CreateTex2D(format);
	CreateShaderResourceView(format);
	CreateSamplerState(format);
}

void EvaEngine::Texture2D::CreateTex2D(const DXGI_FORMAT& format)
{
	D3D11_TEXTURE2D_DESC textureDesc;
	memset(&textureDesc, 0, sizeof(textureDesc));
	textureDesc.ArraySize = 1;
	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	textureDesc.Format = format;
	textureDesc.Width = texelSize.x;
	textureDesc.Height = texelSize.y;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.MipLevels = 1;

	ID3D11Texture2D* texture{ nullptr };
	HRESULT hr = DirectX11App::g_Device->CreateTexture2D(&textureDesc, nullptr, &texture);
	if (FAILED(hr)) {
		DebugLog::LogError("Failed : CreateTexture2D in Texture2D");
		return;
	}

	m_Texture = texture;
}

void EvaEngine::Texture2D::CreateShaderResourceView(const DXGI_FORMAT& format)
{
	D3D11_SHADER_RESOURCE_VIEW_DESC desc;
	memset(&desc, 0, sizeof(desc));
	desc.Format = format;
	desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	desc.Texture2D.MipLevels = 1;

	HRESULT hr = DirectX11App::g_Device->CreateShaderResourceView(m_Texture, &desc, &m_ShaderResourceView);
	if (FAILED(hr)) DebugLog::LogError("Failed : CreateShaderResourceView in Texture2D");
}

void EvaEngine::Texture2D::CreateSamplerState(const DXGI_FORMAT& format)
{
	D3D11_SAMPLER_DESC desc;
	memset(&desc, 0, sizeof(desc));
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	desc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	HRESULT hr = DirectX11App::g_Device->CreateSamplerState(&desc, &m_SamplerState);
	if (FAILED(hr)) DebugLog::LogError("Failed : CreateSamplerState in Texture2D");
}


//void EvaEngine::Texture2D::Apply()
//{
//}

void STDMETHODCALLTYPE Texture2D::GetD3DTexture2DDESC(_Out_ D3D11_TEXTURE2D_DESC* pDesc)
{
	GetD3DTexture2D()->GetDesc(pDesc);
}

ID3D11Texture2D* EvaEngine::Texture2D::GetD3DTexture2D() const
{
	return static_cast<ID3D11Texture2D*>(m_Texture);
}