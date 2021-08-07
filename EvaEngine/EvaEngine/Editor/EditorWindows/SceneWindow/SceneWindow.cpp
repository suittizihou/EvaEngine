#include "SceneWindow.h"
#include "../../SceneView/SceneView.h"
#include "../../../GameSystemBase/Components/Camera/Camera.h"
#include "../../../Utility/Texture/RenderTexture/RenderTexture.h"
#include "../../../App/EditorApp/EditorApp.h"
#include "../../EditorApplication/EditorApplication.h"

using namespace EvaEngine::Editor;
using namespace EvaEngine::Editor::Internal;

SceneWindow::SceneWindow(const std::string& windowPath) :
	EditorWindow(windowPath, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoNav)
{

}

void SceneWindow::OnGUI()
{
	EditorApplication::sceneWindowIsActive = ImGui::IsWindowFocused(ImGuiFocusedFlags_RootWindow);

	// �V�[���r���[�̕`��
	auto windowSize = ImGui::GetWindowSize();
	auto sceneView = EditorApp::GetSceneView();
	// SceneWindow���A�N�e�B�u�łȂ��ꍇ�͑���s�\
	auto camera = sceneView.lock()->GetSceneCamera();
	auto tagetTexture = camera.lock()->targetTexture;
	auto size = tagetTexture->GetTexelSize();
	camera.lock()->SetViewport(windowSize.x, windowSize.y);
	ImGui::Image((void*)tagetTexture->GetShaderResourceView(), ImVec2(windowSize.x, windowSize.y));
}