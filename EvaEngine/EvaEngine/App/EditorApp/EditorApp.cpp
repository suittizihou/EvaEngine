#if _DEBUG

#include "EditorApp.h"
#include "../../Setting/Window/Window.h"
#include "../../System/DebugLog/DebugLog.h"
#include "../DirectX11App/DirectX11App.h"
#include "../../GameSystemBase/Components/Camera/Camera.h"
#include "../../Utility/Math/Matrix4x4/Matrix4x4.h"
#include "../../Editor/SceneView/SceneView.h"
#include "../../GameSystemBase/DataBase/SceneDataBase/SceneDataBase.h"
#include "../../GameSystemBase/Manager/DrawManager/DrawManager.h"

#include "../../Editor/EditorBaseWindow/EditorBaseWindow.h"
#include "../../Editor/EditorWindows/ConsoleWindow/ConsoleWindow.h"
#include "../../Editor/EditorWindows/SceneWindow/SceneWindow.h"
#include "../../Editor/EditorWindows/GameWindow/GameWindow.h"
#include "../../Editor/EditorWindows/InspectorWindow/InspectorWindow.h"
#include "../../Editor/EditorWindows/ProjectWindow/ProjectWindow.h"
#include "../../Editor/EditorWindows/DemoWindow/DemoWindow.h"

#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>
#include <ImGuizmo.h>
#include <iostream>

#define IMGUI_DISABLE_OBSOLETE_FUNCTIONS

using namespace EvaEngine::Internal;
using namespace EvaEngine::Editor::Internal;

std::shared_ptr<SceneView> EditorApp::m_SceneView{ nullptr };
EditorWindowDataBase EditorApp::m_EditorWindows{};

HRESULT EditorApp::ImGuiSetting()
{
	try {
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		// iniを生成しない
		//io.IniFilename = NULL;
		// 日本語フォントに対応
		//ImFontConfig fontConfig{};
		//fontConfig.MergeMode = true;
		io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\meiryo.ttc", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
		// ドッキング機能を有効化
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		// ダークテーマに設定
		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}
	}
	catch (...) {
		return E_ABORT;
	}

	return S_OK;
}

HRESULT EditorApp::Init()
{
	// ImGuiの初期化
	if (FAILED(ImGuiSetting())) {
		DebugLog::LogError("ImGuiの設定に失敗しました。");
		return E_ABORT;
	}

	if (!ImGui_ImplWin32_Init(Window::g_hWnd)) {
		DebugLog::LogError("ImGui_ImplWin32_Initに失敗しました。");
		ImGui::DestroyContext();
		UnregisterClass(Window::g_wc.lpszClassName, Window::g_wc.hInstance);
		return E_ABORT;
	}
	
	if (!ImGui_ImplDX11_Init(EvaEngine::Internal::DirectX11App::g_Device.Get(), EvaEngine::Internal::DirectX11App::g_Context.Get())) {
		DebugLog::LogError("ImGui_ImplDX11_Initに失敗しました。");
		ImGui::DestroyContext();
		UnregisterClass(Window::g_wc.lpszClassName, Window::g_wc.hInstance);
		return E_ABORT;
	}

	// EditorWindowの追加
	m_EditorWindows.CreateEditorWindow<Editor::Internal::EditorBaseWindow>("");
	m_EditorWindows.CreateEditorWindow<Editor::Internal::ConsoleWindow>("Window/General/Console");
	m_EditorWindows.CreateEditorWindow<Editor::Internal::SceneWindow>("Window/General/Scene");
	m_EditorWindows.CreateEditorWindow<Editor::Internal::GameWindow>("Window/General/Game");
	m_EditorWindows.CreateEditorWindow<Editor::Internal::InspectorWindow>("Window/General/Inspector");
	m_EditorWindows.CreateEditorWindow<Editor::Internal::ProjectWindow>("Window/General/Project");
	m_EditorWindows.CreateEditorWindow<Editor::Internal::DemoWindow>("Help/DemoWindow");

	// シーンビューの作成
	m_SceneView = std::make_unique<SceneView>();

	return S_OK;
}

void EditorApp::DrawBegin()
{
	// DepthViewとStencilViewのクリア
	DirectX11App::g_Context->ClearDepthStencilView(
		DirectX11App::g_EditorDepthStencilView.Get(),			// クリア対象のView
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,		// クリアフラグ
		1.0f,											// 深度クリア値
		0);												// ステンシルクリア値

	// シェーダーのセット
	Shader shader{ DrawManager::GetDefaultShader() };
	DrawManager::SetShader(&shader);

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void EditorApp::Draw()
{
	m_EditorWindows.Draw();
	SceneDataBase::Instance().OnGUI();
}

void EditorApp::DrawEnd()
{
	ImGui::Render();
	// レンダーターゲットの設定
	DirectX11App::g_Context->OMSetRenderTargets(1, DirectX11App::g_EditorRenderTargetView.GetAddressOf(), DirectX11App::g_EditorDepthStencilView.Get());

	// 指定色で画面クリア
	float clearColor[4] = { 1.0f, 1.0f, 0.8f, 1.0f };
	// RenderTargetViewのクリア
	DirectX11App::g_Context->ClearRenderTargetView(DirectX11App::g_EditorRenderTargetView.Get(), clearColor);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}
}

void EditorApp::End()
{
	// ImGuiの解放
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

std::shared_ptr<SceneView> EditorApp::GetSceneView() {
	return m_SceneView;
}

#endif