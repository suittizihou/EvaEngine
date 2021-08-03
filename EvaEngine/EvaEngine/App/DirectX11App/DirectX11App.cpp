#include "DirectX11App.h"
#include "../../Setting/Window/Window.h"
#include "../../Utility/BufferCreate/BufferCreate.h"

#include "../../GameSystemBase/Base/GameObject/GameObject.h"
#include "../../GameSystemBase/Components/Transform/Transform.h"
#include "../../GameSystemBase/Components/Camera/Camera.h"

#include <DirectXMath.h>

using namespace EvaEngine::Internal;

ID3D11Device* DirectX11App::g_Device{ nullptr };
ID3D11DeviceContext* DirectX11App::g_Context{ nullptr };
IDXGISwapChain* DirectX11App::g_SwapChain{ nullptr };
ID3D11RenderTargetView* DirectX11App::g_EditorRenderTargetView{ nullptr };
ID3D11DepthStencilView* DirectX11App::g_EditorDepthStencilView{ nullptr };
ID3D11Buffer* DirectX11App::g_ConstantBuffer{ nullptr };
ConstantBufferData DirectX11App::g_ConstantBufferData{};

#if _DEBUG
IDXGIDebug* DirectX11App::g_pDxgiDebug{ nullptr };
ID3D11Debug* DirectX11App::g_pD3DDebug{ nullptr };
#endif

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

	// ライトの設定
	DirectX::XMVECTOR light = DirectX::XMVector3Normalize(DirectX::XMVectorSet(0.0f, 0.5f, -1.0f, 0.0f));

	DirectX::XMStoreFloat4(&DirectX11App::g_ConstantBufferData.lightVector, light);

	// ライトのカラー設定
	DirectX11App::g_ConstantBufferData.lightColor = DirectX::XMFLOAT4(0.5f, 0.5f, 0.5f, 1);

	D3D11_VIEWPORT viewPort{ Window::GetViewport() };
	// ビューポートのセットアップ
	g_Context->RSSetViewports(1, &viewPort);

	return hr;
}

void EvaEngine::Internal::DirectX11App::Release()
{
	g_Device->Release();
	g_Device = nullptr;
	g_Context->Release();
	g_Context = nullptr;
	g_SwapChain->Release();
	g_SwapChain = nullptr;
	g_EditorRenderTargetView->Release();
	g_EditorRenderTargetView = nullptr;
	g_EditorDepthStencilView->Release();
	g_EditorDepthStencilView = nullptr;
	g_ConstantBuffer->Release();
	g_ConstantBuffer = nullptr;
	m_Adapter->Release();
	m_Adapter = nullptr;
}

HRESULT DirectX11App::HardWareCheck()
{
	IDXGIFactory* factory{ nullptr };
	IDXGIOutput* adapterOutput{ nullptr };
	UINT numModes{ 0 };
	size_t stringLength{};
	DXGI_ADAPTER_DESC adapterDesc{};

	// グラフィック インターフェース ファクトリを作成
	auto hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
	if (FAILED(hr)) {
		DebugLog::LogError(u8"Graphic Interface Factory Create Failed.");
		return hr;
	}

	int gpuNumber{};
	int gpuMaxMem{};
	// 一番強いGPUアダプタを検索(全アダプタの検索をかけてVRAMが一番多いアダプタを取得)
	for (int adapterNum = 0; factory->EnumAdapters(adapterNum, &m_Adapter) != DXGI_ERROR_NOT_FOUND; ++adapterNum) {
		IDXGIAdapter* add{ nullptr };
		hr = factory->EnumAdapters(adapterNum, &add);
		if (FAILED(hr)) break;

		hr = add->GetDesc(&adapterDesc);

		char videoCardDescription[128];
		// ビデオカード名を取得
		int error = wcstombs_s(&stringLength, videoCardDescription, 128, adapterDesc.Description, 128);

		if (error != 0) break;

		//DebugLog::Log(u8"ビデオカード名 : " + std::string(videoCardDescription, sizeof(videoCardDescription) / sizeof(videoCardDescription[0])));

		// ビデオカードメモリを取得(MB単位)
		int videoCardMemory = static_cast<int>(adapterDesc.DedicatedVideoMemory / 1024 / 1024);
		//DebugLog::Log(u8"ビデオメモリー : " + videoCardMemory);

		// アウトプット(モニター)に番号IDを付ける
		hr = add->EnumOutputs(0, &adapterOutput);
		if (FAILED(hr)) continue;

		// DXGI_FORMAT_R8G8B8A8_UNORM の表示形式数を取得する
		hr = adapterOutput->GetDisplayModeList(DXGI_FORMAT_R8G8B8A8_UNORM, DXGI_ENUM_MODES_INTERLACED, &numModes, NULL);
		if (FAILED(hr)) continue;
		//DebugLog::Log(u8"RGBA8_UNORM Count : " + numModes);

		if (videoCardMemory > gpuMaxMem) {
			gpuMaxMem = videoCardMemory;
			gpuNumber = adapterNum;
		}

		add->Release();
		add = nullptr;

		// アダプタアウトプットを解放
		adapterOutput->Release();
		adapterOutput = nullptr;
	}

	// グラフィック インターフェース アダプターを作成
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
	cdev_flags |= D3D11_CREATE_DEVICE_DEBUG/* | D3D11_CREATE_DEVICE_BGRA_SUPPORT*/ | D3D11_CREATE_DEVICE_SWITCH_TO_REF;
#endif

	// スワップチェイン設定
	DXGI_SWAP_CHAIN_DESC sd{};
	ZeroMemory(&sd, sizeof(DXGI_SWAP_CHAIN_DESC));
	sd.BufferCount = 2;
	sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	sd.BufferDesc.Width = static_cast<UINT>(Window::GetViewport().Width);
	sd.BufferDesc.Height = static_cast<UINT>(Window::GetViewport().Height);
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = Window::g_FPS; // リフレッシュレートの分母
	sd.BufferDesc.RefreshRate.Denominator = 1; // リフレッシュレートの分子
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = Window::g_hWnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = true;

	HRESULT hr{};
	D3D_FEATURE_LEVEL featureLevels{};

	// DirectX11デバイスとスワップチェイン作成
	hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
#if defined(DEBUG) || defined(_DEBUG)
		cdev_flags, 
#else
		D3D11_CREATE_DEVICE_BGRA_SUPPORT,
#endif
		nullptr, 
		0, 
		D3D11_SDK_VERSION, 
		&sd,
		&g_SwapChain, 
		&g_Device, 
		&featureLevels, 
		&g_Context);

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

	// ラスタライザーステートをセット
	DirectX11App::g_Context->RSSetState(rasterizerState);
	rasterizerState->Release();
	rasterizerState = nullptr;

	return hr;
}

HRESULT DirectX11App::CreateRenderTargetView()
{
	HRESULT hr{};
	ID3D11Texture2D* backBuffer{ nullptr };
	
	// スワップチェインに用意されたバッファ(2Dテクスチャ)を取得
	hr = g_SwapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
	if (FAILED(hr)) {
		DebugLog::LogError(u8"Buffer Texture Get Failed.");
		return hr;
	}

	// レンダーターゲットView作成
	hr = g_Device->CreateRenderTargetView(backBuffer, NULL, &g_EditorRenderTargetView);
	if (FAILED(hr)) {
		DebugLog::LogError(u8"Render Target View Create Failed.");
		return hr;
	}

	// 使い終わったものを解放
	backBuffer->Release();
	backBuffer = nullptr;

	return hr;
}

HRESULT DirectX11App::CreateDepthAndStencilView()
{
	HRESULT hr{};

	// 深度ステンシルバッファの作成
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

	hr = g_Device->CreateDepthStencilView(depthStencil, &dsvDesc, &g_EditorDepthStencilView);
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

void DirectX11App::SetConstantBuffer(const std::weak_ptr<EvaEngine::Camera>& camera)
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

void EvaEngine::Internal::DirectX11App::ReportLiveObjects()
{
	OSVERSIONINFOEX OSver;
	ULONGLONG condition = 0;
	OSver.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
	OSver.dwMajorVersion = 6;
	OSver.dwMinorVersion = 2;
	VER_SET_CONDITION(condition, VER_MAJORVERSION, VER_GREATER_EQUAL);
	VER_SET_CONDITION(condition, VER_MINORVERSION, VER_GREATER_EQUAL);

	if (VerifyVersionInfo(&OSver, VER_MAJORVERSION | VER_MINORVERSION, condition))
	{
		// Widows8.0以上なら
		if (g_pDxgiDebug == nullptr)
		{
			// 作成
			typedef HRESULT(__stdcall* fPtr)(const IID&, void**);
			HMODULE hDll = GetModuleHandleW(L"dxgidebug.dll");
			fPtr DXGIGetDebugInterface = (fPtr)GetProcAddress(hDll, "DXGIGetDebugInterface");

			DXGIGetDebugInterface(__uuidof(IDXGIDebug), (void**)&g_pDxgiDebug);

			// 出力
			g_pDxgiDebug->ReportLiveObjects(DXGI_DEBUG_D3D11, DXGI_DEBUG_RLO_DETAIL);
		}
		else
			g_pDxgiDebug->ReportLiveObjects(DXGI_DEBUG_D3D11, DXGI_DEBUG_RLO_DETAIL);
	}
	else
	{
		g_Device->QueryInterface(__uuidof(ID3D11Debug), reinterpret_cast<void**>(&g_pD3DDebug));
		g_pD3DDebug->ReportLiveDeviceObjects(D3D11_RLDO_DETAIL);
	}
}

void EvaEngine::Internal::DirectX11App::DebugRelease()
{
	if (g_pD3DDebug != nullptr) {
		g_pD3DDebug->Release();
		g_pD3DDebug = nullptr;
	}

	if (g_pDxgiDebug != nullptr) {
		g_pDxgiDebug->Release();
		g_pDxgiDebug = nullptr;
	}
}
