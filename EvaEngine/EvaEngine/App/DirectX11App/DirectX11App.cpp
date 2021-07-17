#include "DirectX11App.h"
#include "../../Setting/Window/Window.h"
#include "../../Utility/BufferCreate/BufferCreate.h"

#include "../../GameSystemBase/Base/GameObject/GameObject.h"
#include "../../GameSystemBase/Components/Transform/Transform.h"
#include "../../GameSystemBase/Components/Camera/Camera.h"

#include <DirectXMath.h>

using namespace EvaEngine;

D3DDevice DirectX11App::g_Device{ nullptr };
D3DContext DirectX11App::g_Context{ nullptr };
SwapChain DirectX11App::g_SwapChain{ nullptr };
RenderTargetView DirectX11App::g_RenderTargetView{ nullptr };
DepthStencilView DirectX11App::g_DepthStencilView{ nullptr };
ConstantBuffer DirectX11App::g_ConstantBuffer{ nullptr };
ConstantBufferData DirectX11App::g_ConstantBufferData{};

IDXGIAdapter* DirectX11App::m_Adapter{ nullptr };

HRESULT DirectX11App::Init()
{
	HRESULT hr{};
	hr = HardWareCheck();
	if (FAILED(hr)) {
		DebugLog::LogError(u8"Hard Ware Check Failed.");
		return hr;
	}

	hr = CreateDeviceAndSwapChain();
	if (FAILED(hr)) {
		DebugLog::LogError(u8"Swap Chain or Device Create Failed.");
		return hr;
	}

	hr = CreateRasterizerState();
	if (FAILED(hr)) {
		DebugLog::LogError(u8"Rasterizer State Create Failed.");
		return hr;
	}

	hr = CreateRenderTargetView();
	if (FAILED(hr)) {
		DebugLog::LogError(u8"Render Target View Create Failed.");
		return hr;
	}

	hr = CreateDepthAndStencilView();
	if (FAILED(hr)) {
		DebugLog::LogError(u8"Depth Stencil View Create Failed.");
		return hr;
	}

	hr = CreateConstantBuffer();
	if (FAILED(hr)) {
		DebugLog::LogError(u8"Constant Buffer Create Failed.");
		return hr;
	}

	// ���C�g�̐ݒ�
	DirectX::XMVECTOR light = DirectX::XMVector3Normalize(DirectX::XMVectorSet(0.0f, 0.5f, -1.0f, 0.0f));

	DirectX::XMStoreFloat4(&DirectX11App::g_ConstantBufferData.lightVector, light);

	// ���C�g�̃J���[�ݒ�
	DirectX11App::g_ConstantBufferData.lightColor = DirectX::XMFLOAT4(0.5f, 0.5f, 0.5f, 1);

	D3D11_VIEWPORT viewPort{ Window::GetViewport() };
	// �r���[�|�[�g�̃Z�b�g�A�b�v
	g_Context->RSSetViewports(1, &viewPort);

	return hr;
}

HRESULT DirectX11App::HardWareCheck()
{
	IDXGIFactory* factory{ nullptr };
	IDXGIOutput* adapterOutput{ nullptr };
	UINT numModes{ 0 };
	size_t stringLength{};
	DXGI_ADAPTER_DESC adapterDesc{};

	// �O���t�B�b�N �C���^�[�t�F�[�X �t�@�N�g�����쐬
	auto hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	if (FAILED(hr)) {
		DebugLog::LogError(u8"Graphic Interface Factory Create Failed.");
		return hr;
	}

	int gpuNumber{};
	int gpuMaxMem{};
	// ��ԋ���GPU�A�_�v�^������(�S�A�_�v�^�̌�����������VRAM����ԑ����A�_�v�^���擾)
	for (int adapterNum = 0; factory->EnumAdapters(adapterNum, &m_Adapter) != DXGI_ERROR_NOT_FOUND; ++adapterNum) {
		IDXGIAdapter* add{ nullptr };
		hr = factory->EnumAdapters(adapterNum, &add);
		if (FAILED(hr)) break;

		hr = add->GetDesc(&adapterDesc);

		char videoCardDescription[128];
		// �r�f�I�J�[�h�����擾
		int error = wcstombs_s(&stringLength, videoCardDescription, 128, adapterDesc.Description, 128);

		if (error != 0) break;

		//DebugLog::Log(u8"�r�f�I�J�[�h�� : " + std::string(videoCardDescription, sizeof(videoCardDescription) / sizeof(videoCardDescription[0])));

		// �r�f�I�J�[�h���������擾(MB�P��)
		int videoCardMemory = static_cast<int>(adapterDesc.DedicatedVideoMemory / 1024 / 1024);
		//DebugLog::Log(u8"�r�f�I�������[ : " + videoCardMemory);

		// �A�E�g�v�b�g(���j�^�[)�ɔԍ�ID��t����
		hr = add->EnumOutputs(0, &adapterOutput);
		if (FAILED(hr)) continue;

		// DXGI_FORMAT_R8G8B8A8_UNORM �̕\���`�������擾����
		hr = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
		if (FAILED(hr)) continue;
		//DebugLog::Log(u8"RGBA8_UNORM Count : " + numModes);

		if (videoCardMemory > gpuMaxMem) {
			gpuMaxMem = videoCardMemory;
			gpuNumber = adapterNum;
		}

		add->Release();
		add = nullptr;

		// �A�_�v�^�A�E�g�v�b�g�����
		adapterOutput->Release();
		adapterOutput = nullptr;
	}

	// �O���t�B�b�N �C���^�[�t�F�[�X �A�_�v�^�[���쐬
	hr = factory->EnumAdapters(gpuNumber, &m_Adapter);
	if (FAILED(hr)) return hr;

	factory->Release();
	factory = nullptr;

	return hr;
}

HRESULT DirectX11App::CreateDeviceAndSwapChain()
{
	UINT cdev_flags{};
#ifdef _DEBUG
	cdev_flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// �X���b�v�`�F�C���ݒ�
	DXGI_SWAP_CHAIN_DESC sd{};
	ZeroMemory(&sd, sizeof(DXGI_SWAP_CHAIN_DESC));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = static_cast<UINT>(Window::GetViewport().Width);
	sd.BufferDesc.Height = static_cast<UINT>(Window::GetViewport().Height);
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = Window::g_FPS;
	sd.BufferDesc.RefreshRate.Denominator = 1; // 1 / 60 = 60fps
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = Window::g_hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = true;


	HRESULT hr{};
	D3D_FEATURE_LEVEL featureLevels{};

	// DirectX11�f�o�C�X�ƃX���b�v�`�F�C���쐬
	hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		cdev_flags, 
		nullptr, 
		0, 
		D3D11_SDK_VERSION, 
		&sd,
		&g_SwapChain, 
		&g_Device, 
		&featureLevels, 
		&g_Context);

	// �A�_�v�^�[�̉��
	m_Adapter->Release();
	m_Adapter = nullptr;

	return hr;
}

HRESULT DirectX11App::CreateRasterizerState()
{
	HRESULT hr{};
	ID3D11RasterizerState* rasterizerState{ nullptr };

	D3D11_RASTERIZER_DESC rasterizerDesc{};
	ZeroMemory(&rasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_BACK;

	hr = DirectX11App::g_Device->CreateRasterizerState(&rasterizerDesc, &rasterizerState);
	if (FAILED(hr)) {
		DebugLog::LogError(u8"Rasterizer State Create Failed.");
		return hr;
	}

	// ���X�^���C�U�[�X�e�[�g���Z�b�g
	DirectX11App::g_Context->RSSetState(rasterizerState);
	rasterizerState->Release();
	rasterizerState = nullptr;

	return hr;
}

HRESULT DirectX11App::CreateRenderTargetView()
{
	HRESULT hr{};
	ID3D11Texture2D* backBuffer{ nullptr };

	// �X���b�v�`�F�C���ɗp�ӂ��ꂽ�o�b�t�@(2D�e�N�X�`��)���擾
	hr = g_SwapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
	if (FAILED(hr)) {
		DebugLog::LogError(u8"Buffer Texture Get Failed.");
		return hr;
	}

	// �����_�[�^�[�Q�b�gView�쐬
	hr = g_Device->CreateRenderTargetView(backBuffer, NULL, g_RenderTargetView.GetAddressOf());
	if (FAILED(hr)) {
		DebugLog::LogError(u8"Render Target View Create Failed.");
		return hr;
	}

	// �g���I��������̂����
	backBuffer->Release();
	backBuffer = nullptr;

	return hr;
}

HRESULT DirectX11App::CreateDepthAndStencilView()
{
	HRESULT hr{};

	// �[�x�X�e���V���o�b�t�@�̍쐬
	D3D11_TEXTURE2D_DESC textureDesc{};
	ZeroMemory(&textureDesc, sizeof(D3D11_TEXTURE2D_DESC));
	textureDesc.Width = static_cast<UINT>(Window::GetViewport().Width);
	textureDesc.Height = static_cast<UINT>(Window::GetViewport().Height);
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

	hr = g_Device->CreateTexture2D(&textureDesc, NULL, &depthStencil);
	if (FAILED(hr)) {
		DebugLog::LogError(u8"Depth Stencil Texture Create Failed.");
		return hr;
	}

	CD3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc{};
	ZeroMemory(&dsvDesc, sizeof(dsvDesc));
	dsvDesc.Format = textureDesc.Format;
	dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvDesc.Texture2D.MipSlice = 0;

	hr = g_Device->CreateDepthStencilView(depthStencil, &dsvDesc, &g_DepthStencilView);
	if(FAILED(hr)){
		DebugLog::LogError(u8"Depth Stencill View Create Failed");
		return hr;
	}

	depthStencil->Release();
	depthStencil = nullptr;

	return hr;
}

HRESULT DirectX11App::CreateConstantBuffer()
{
	g_ConstantBuffer = BufferCreate::CreateConstantBuffer();
	if (g_ConstantBuffer == nullptr) {
		return E_FAIL;
	}
	return S_OK;
}

void DirectX11App::SetConstantBuffer(const std::weak_ptr<Camera>& camera)
{
	DirectX::XMVECTOR light = DirectX::XMVector3Normalize(DirectX::XMVectorSet(0.0f, 0.5f, -1.0f, 0.0f));

	DirectX::XMStoreFloat4x4(&g_ConstantBufferData.view, DirectX::XMMatrixTranspose(camera.lock()->GetViewMatrixDxMath()));
	DirectX::XMStoreFloat4x4(&g_ConstantBufferData.projection, DirectX::XMMatrixTranspose(camera.lock()->GetProjectionMatrixDxMath()));
	DirectX::XMStoreFloat4(&g_ConstantBufferData.lightVector, light);
	DirectX::XMStoreFloat4(&g_ConstantBufferData.cameraPos, 
		DirectX::XMVectorSet(
		camera.lock()->GetTransform().lock()->position().x,
		camera.lock()->GetTransform().lock()->position().y,
		camera.lock()->GetTransform().lock()->position().z,
		0.0f));
	g_ConstantBufferData.lightColor = DirectX::XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
}