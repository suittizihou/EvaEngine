#include "Texture2D.h"
#include "../../../App/DirectX11App/DirectX11App.h"

using namespace EvaEngine;
using namespace EvaEngine::Internal;

EvaEngine::Texture2D::Texture2D(const UINT width, const UINT height)
{
	memset(&m_TextureDesc, 0, sizeof(m_TextureDesc));
	m_TextureDesc.Usage = D3D11_USAGE_DEFAULT;
	m_TextureDesc.Format = DXGI_FORMAT_R8G8B8A8_TYPELESS;
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

EvaEngine::Texture2D::Texture2D(const UINT width, const UINT height, const DXGI_FORMAT& textureFormat)
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

EvaEngine::Texture2D::Texture2D(const UINT width, const UINT height, const D3D11_TEXTURE2D_DESC& textureDesc)
{
	this->m_TextureDesc = textureDesc;
	Init();
}

EvaEngine::Texture2D::~Texture2D()
{
	if(m_Texture2D != nullptr)
		m_Texture2D->Release();
}

void STDMETHODCALLTYPE Texture2D::GetD3DTexture2D(_Out_ D3D11_TEXTURE2D_DESC* pDesc)
{
	return m_Texture2D->GetDesc(pDesc);
}

void EvaEngine::Texture2D::Init()
{
	textureType = TextureType::Tex2D;
	Create();
}

void EvaEngine::Texture2D::Create()
{
	HRESULT hr = DirectX11App::g_Device->CreateTexture2D(&m_TextureDesc, NULL, &m_Texture2D);
	if (FAILED(hr)) DebugLog::LogError("Texture2D‚Ìì¬‚É¸”s‚µ‚Ü‚µ‚½B");
}