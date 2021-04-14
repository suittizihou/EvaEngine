#include "EvaEngineApp.h"
#include "../../Setting/Window/Window.h"
#include "../DirectX11App/DirectX11App.h"
#include "../../GameSystemBase/DataBase/ModelDataBase/ModelDataBase.h"
#include "../../GameSystemBase/DataBase/ShaderDataBase/ShaderDataBase.h"
#include "../../GameSystemBase/DataBase/TextureDataBase/TextureDataBase.h"
#include "../../GameSystemBase/DataBase/SceneDataBase/SceneDataBase.h"
#include "../../GameSystemBase/Manager/DrawManager/DrawManager.h"

#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>
#include <iostream>

using namespace EvaEngine;

EvaEngineApp::~EvaEngineApp() {
}

HRESULT EvaEngineApp::Init()
{
	HRESULT hr{};

	// 描画マネージャーの初期化
	hr = DrawManager::Init();
	if (FAILED(hr)) {
		DebugLog::LogError("DrawManagerの初期化に失敗しました。");
		return hr;
	}

	// シーンの初期化
	hr = SceneDataBase::Instance().InitializeScene();
	if (FAILED(hr)) {
		DebugLog::LogError("シーンの初期化に失敗しました。");
		return hr;
	}

	// ImGuiの初期化
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsLight();

	if (!ImGui_ImplWin32_Init(Window::g_hWnd)) {
		DebugLog::LogError("ImGui_ImplWin32_Initに失敗しました。");
		ImGui::DestroyContext();
		UnregisterClass(Window::g_wc.lpszClassName, Window::g_wc.hInstance);
		hr = E_ABORT;
		return hr;
	}

	if (!ImGui_ImplDX11_Init(DirectX11App::g_Device.Get(), DirectX11App::g_Context.Get())) {
		DebugLog::LogError("ImGui_ImplDX11_Initに失敗しました。");
		ImGui::DestroyContext();
		UnregisterClass(Window::g_wc.lpszClassName, Window::g_wc.hInstance);
		hr = E_ABORT;
		return hr;
	}

	// iniを生成しない
	io.IniFilename = NULL;
	// 日本語フォントに対応
	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\meiryo.ttc", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());

	return S_OK;
}

void EvaEngineApp::Update()
{
	SceneDataBase::Instance().SceneUpdate();
	SceneDataBase::Instance().FixedUpdate();
	SceneDataBase::Instance().Update();
	SceneDataBase::Instance().LateUpdate();
}

void EvaEngineApp::Draw(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& command)
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// 描画開始処理
	DrawManager::DrawBegin();

	// ポリゴンの種類
	DirectX11App::g_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// シェーダーのセット
	Shader shader{ DrawManager::GetDefaultShader() };
	DrawManager::SetShader(shader);
	// レンダーターゲットの設定
	DirectX11App::g_Context->OMSetRenderTargets(1, DirectX11App::g_RenderTargetView.GetAddressOf(), DirectX11App::g_DepthStencilView.Get());

	// 描画
	SceneDataBase::Instance().Draw(command);

	ImGui::Begin("Test Window");

	ImGui::Text("Hello world");

	if (ImGui::Button("OK")) {
		std::cout << "Button" << std::endl;
	}

	static float f = 0.0f;
	if (ImGui::SliderFloat("float", &f, 0.0f, 1.0f)) {
		std::cout << "SliderFloat" << std::endl;
	}

	ImGui::End();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	// 描画終了処理
	DrawManager::DrawEnd();
}

void EvaEngineApp::FrameEnd()
{
	SceneDataBase::Instance().SceneChange();
}

void EvaEngine::EvaEngineApp::End()
{
	// ImGuiの解放
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}
