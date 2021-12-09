#include "Texture2D.h"
#include "../../../App/DirectX11App/DirectX11App.h"

using namespace EvaEngine;
using namespace EvaEngine::Internal;

EvaEngine::Texture2D::Texture2D(const UINT width, const UINT height) : Texture(width, height)
{
	memset(&m_TextureDesc, 0, sizeof(m_TextureDesc));
	m_TextureDesc.ArraySize = 1;
	m_TextureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	m_TextureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	m_TextureDesc.Width = width;
	m_TextureDesc.Height = height;
	m_TextureDesc.Usage = D3D11_USAGE_DEFAULT;
	m_TextureDesc.SampleDesc.Count = 1;
	m_TextureDesc.MipLevels = 1;

	Init();
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
	ID3D11Texture2D* texture{ nullptr };
	HRESULT hr = DirectX11App::g_Device->CreateTexture2D(&m_TextureDesc, nullptr, &texture);
	if (FAILED(hr)) {
		DebugLog::LogError(u8"Failed : CreateTexture2D in Texture2D");
		return;
	}
	m_Texture = texture;
}

void STDMETHODCALLTYPE Texture2D::GetD3DTexture2DDESC(_Out_ D3D11_TEXTURE2D_DESC* pDesc)
{
	GetD3DTexture2D()->GetDesc(pDesc);
}

ID3D11Texture2D* EvaEngine::Texture2D::GetD3DTexture2D() const
{
	return static_cast<ID3D11Texture2D*>(m_Texture);
}

void EvaEngine::Texture2D::CreateShaderResourceView(const D3D11_SHADER_RESOURCE_VIEW_DESC& desc)
{
	HRESULT hr = Internal::DirectX11App::g_Device->CreateShaderResourceView(m_Texture, &desc, &m_ShaderResourceView);

	if (FAILED(hr)) DebugLog::LogError(u8"Failed : CreateShaderResourceView in Texture2D");
}

void EvaEngine::Texture2D::CreateSamplerState(const D3D11_SAMPLER_DESC& desc)
{
	HRESULT hr = Internal::DirectX11App::g_Device->CreateSamplerState(&desc, &m_SamplerState);

	if (FAILED(hr)) DebugLog::LogError(u8"Failed : CreateSamplerState in Texture2D");
}