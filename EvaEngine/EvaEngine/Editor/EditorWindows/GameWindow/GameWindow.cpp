#if _DEBUG
#include "GameWindow.h"
#include "../../../GameSystemBase/Components/Camera/Camera.h"
#include "../../../Utility/Texture/RenderTexture/RenderTexture.h"
#include "../../EditorApplication/EditorApplication.h"

using namespace EvaEngine::Editor;

void EvaEngine::Editor::Internal::GameWindow::Init()
{
	windowFlags |= ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoNav;
}

void EvaEngine::Editor::Internal::GameWindow::OnGUI()
{
	EditorApplication::gameWindowIsActive = ImGui::IsWindowFocused(ImGuiFocusedFlags_RootWindow);

	auto windowSize = ImGui::GetWindowSize();

	// 全カメラ情報を取得し、テクスチャとしてGameWindowに描画
	auto cameras = Camera::GetAllCamera();
	for (int i = 0; i < cameras.size(); ++i) {
		auto tagetTexture = cameras[i].lock()->targetTexture;
		auto size = tagetTexture->GetTexelSize();
		cameras[i].lock()->SetViewport(size.x, size.y);
		// アスペクト比を保つ
		windowSize.y = windowSize.x / size.x * size.y;
		ImGui::Image((void*)tagetTexture->GetShaderResourceView(), ImVec2(windowSize.x, windowSize.y));
	}
}
#endif