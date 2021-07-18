#if _DEBUG

#include "EditorApp.h"
#include "../../Setting/Window/Window.h"
#include "../../System/DebugLog/DebugLog.h"
#include "../DirectX11App/DirectX11App.h"
#include "../../GameSystemBase/Components/Camera/Camera.h"
#include "../../Utility/Math/Matrix4x4/Matrix4x4.h"
#include "../../Editor/SceneView/SceneView.h"
#include "../../GameSystemBase/DataBase/SceneDataBase/SceneDataBase.h"

#include "../../Editor/EditorBaseWindow/EditorBaseWindow.h"
#include "../../Editor/EditorWindows/ConsoleWindow/ConsoleWindow.h"

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
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		// iniを生成しない
		//io.IniFilename = NULL;
		// 日本語フォントに対応
		//ImFontConfig fontConfig{};
		//fontConfig.MergeMode = true;
		io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\meiryo.ttc", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
		// ドッキング機能を有効化
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
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

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
	m_EditorWindows.CreateEditorWindow<Editor::Internal::EditorBaseWindow>("Window");
	m_EditorWindows.CreateEditorWindow<Editor::Internal::ConsoleWindow>("Window");

	// シーンビューの作成
	m_SceneView = std::make_unique<SceneView>();

	return S_OK;
}

void EditorApp::DrawBegin()
{
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