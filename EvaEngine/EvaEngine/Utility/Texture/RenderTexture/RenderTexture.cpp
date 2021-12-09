#include "RenderTexture.h"

#include "../../../App/DirectX11App/DirectX11App.h"
#include "../Texture2D/Texture2D.h"

using namespace EvaEngine::Internal;

EvaEngine::RenderTexture::RenderTexture(const UINT width, const UINT height) : Texture(width, height)
{
}

EvaEngine::RenderTexture::~RenderTexture()
{
}

void EvaEngine::RenderTexture::Create()
{
	DXGI_FORMAT format{ DXGI_FORMAT_R8G8B8A8_UNORM };
	CreateTex2D(format);
	CreateRenderTargetView(format);
	CreateShaderResourceView(format);
	CreateDepthStencilView();
	CreateSamplerState();
}

void EvaEngine::RenderTexture::Release()
{
	if (m_Texture != nullptr) {
		m_Texture->Release();
		m_Texture = nullptr;
	}

	if (m_RenderTargetView != nullptr) {
		m_RenderTargetView->Release();
		m_RenderTargetView = nullptr;
	}

	if (m_ShaderResourceView != nullptr) {
		m_ShaderResourceView->Release();
		m_ShaderResourceView = nullptr;
	}

	if (m_DepthStencilView != nullptr) {
		m_DepthStencilView->Release();
		m_DepthStencilView = nullptr;
	}

	if (m_SamplerState != nullptr) {
		m_SamplerState->Release();
		m_SamplerState = nullptr;
	}
}

void EvaEngine::RenderTexture::SetRenderTarget(const Color& clearColor) const
{
	// ポリゴンの生成方法の指定
	DirectX11App::g_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	// レンダーターゲットを設定
	DirectX11App::g_Context->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);

	// レンダーターゲットをクリア
	float color[4] = { clearColor.r, clearColor.g, clearColor.b, clearColor.a };
	DirectX11App::g_Context->ClearRenderTargetView(m_RenderTargetView, color);
	// 深度ステンシルバッファをクリア
	DirectX11App::g_Context->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

ID3D11ShaderResourceView* EvaEngine::RenderTexture::GetShaderResourceView() const
{
	return m_ShaderResourceView;
}

void EvaEngine::RenderTexture::CreateTex2D(const DXGI_FORMAT& format)
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
		DebugLog::LogError(u8"Failed : CreateTexture2D in Texture2D");
		return;
	}
	
	m_Texture = texture;
}

void EvaEngine::RenderTexture::CreateRenderTargetView(const DXGI_FORMAT& format)
{
	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
	memset(&rtvDesc, 0, sizeof(rtvDesc));
	rtvDesc.Format = format;
	rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	HRESULT hr = DirectX11App::g_Device->CreateRenderTargetView(m_Texture , &rtvDesc, &m_RenderTargetView);
	if (FAILED(hr)) {
		DebugLog::LogError(u8"Failed : CreateRenderTargetView in RenderTexture");
		return;
	}
}

void EvaEngine::RenderTexture::CreateShaderResourceView(const DXGI_FORMAT& format)
{
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	memset(&srvDesc, 0, sizeof(srvDesc));
	srvDesc.Format = format;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;

	HRESULT hr = DirectX11App::g_Device->CreateShaderResourceView(m_Texture, &srvDesc, &m_ShaderResourceView);
	if (FAILED(hr)) {
		DebugLog::LogError(u8"Failed : CreateShaderResourceView in RenderTexture");
		return;
	}
}

void EvaEngine::RenderTexture::CreateDepthStencilView()
{
	// 深度ステンシルバッファの作成
	D3D11_TEXTURE2D_DESC textureDesc{};
	ZeroMemory(&textureDesc, sizeof(D3D11_TEXTURE2D_DESC));
	textureDesc.Width = static_cast<UINT>(texelSize.x);
	textureDesc.Height = static_cast<UINT>(texelSize.y);
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.SampleDesc.Quality = 0;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	ID3D11Texture2D* depthStencil{ nullptr };

	HRESULT hr = DirectX11App::g_Device->CreateTexture2D(&textureDesc, NULL, &depthStencil);
	if (FAILED(hr)) {
		DebugLog::LogError(u8"Failed : CreateTexture2D in RenderTexture");
		return;
	}

	CD3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc{};
	ZeroMemory(&dsvDesc, sizeof(dsvDesc));
	dsvDesc.Format = textureDesc.Format;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;

	hr = DirectX11App::g_Device->CreateDepthStencilView(depthStencil, &dsvDesc, &m_DepthStencilView);
	if (FAILED(hr)) {
		DebugLog::LogError(u8"Failed : CreateDepthStencilView in RenderTexture");
		depthStencil->Release();
		depthStencil = nullptr;
		return;
	}

	depthStencil->Release();
	depthStencil = nullptr;
}

void EvaEngine::RenderTexture::CreateSamplerState() {
	D3D11_SAMPLER_DESC smpDesc;
	memset(&smpDesc, 0, sizeof(smpDesc));
	smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	smpDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	smpDesc.MinLOD = 0;
	smpDesc.MaxLOD = D3D11_FLOAT32_MAX;

	HRESULT hr = DirectX11App::g_Device->CreateSamplerState(&smpDesc, &m_SamplerState);
	if (FAILED(hr)) {
		DebugLog::LogError(u8"Failed : CreateSamplerState in RenderTexture");
		return;
	}
}

//void EvaEngine::RenderTexture::CreateTex3D()
//{
//	D3D11_TEXTURE2D_DESC textureDesc;
//	memset(&textureDesc, 0, sizeof(textureDesc));
//	textureDesc.ArraySize = 1;
//	textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
//	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//	textureDesc.Width = texelSize.x;
//	textureDesc.Height = texelSize.y;
//	textureDesc.Usage = D3D11_USAGE_DEFAULT;
//	textureDesc.SampleDesc.Count = 1;
//	textureDesc.MipLevels = 1;
//
//	ID3D11Texture2D* texture{ nullptr };
//	HRESULT hr = DirectX11App::g_Device->CreateTexture2D(&textureDesc, nullptr, &texture);
//	if (FAILED(hr)) {
//		DebugLog::LogError(u8"Failed : CreateTexture2D in Texture2D");
//		return;
//	}
//	m_Texture = texture;
//
//}
