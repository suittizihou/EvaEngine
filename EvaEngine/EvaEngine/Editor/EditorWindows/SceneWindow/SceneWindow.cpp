#include "SceneWindow.h"
#include "../../SceneView/SceneView.h"
#include "../../../GameSystemBase/Components/Camera/Camera.h"
#include "../../../Utility/Texture/RenderTexture/RenderTexture.h"
#include "../../../App/EditorApp/EditorApp.h"

using namespace EvaEngine::Editor::Internal;

SceneWindow::SceneWindow(const std::string& windowPath) :
	EditorWindow(windowPath, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoNav)
{

}

void SceneWindow::OnGUI()
{
	// シーンビューの描画

	auto windowSize = ImGui::GetWindowSize();
	auto camera = EditorApp::GetSceneView().lock()->GetSceneCamera();
	auto tagetTexture = camera.lock()->targetTexture;
	auto size = tagetTexture->GetTexelSize();
	camera.lock()->SetViewport(windowSize.x, windowSize.y);
	ImGui::Image((void*)tagetTexture->GetShaderResourceView(), ImVec2(windowSize.x, windowSize.y));
}