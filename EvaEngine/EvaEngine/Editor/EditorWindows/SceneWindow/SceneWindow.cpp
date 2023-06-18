#include "SceneWindow.h"
#include "../../SceneView/SceneView.h"
#include "../../../GameSystemBase/Components/Camera/Camera.h"
#include "../../../Utility/Texture/RenderTexture/RenderTexture.h"
#include "../../../App/EditorApp/EditorApp.h"
#include "../../EditorApplication/EditorApplication.h"
#include "../../EditorCommand/EditorCommand.h"
#include "../../Selection/Selection.h"
#if _DEBUG
#include "../../../GameSystemBase/Base/GameObject/GameObject.h"
#include "../../../GameSystemBase/Components/Transform/Transform.h"
#include "../../../Setting/Window/Window.h"

#include <ImGuizmo.h>

using namespace EvaEngine::Editor;
using namespace EvaEngine::Editor::Internal;

SceneWindow::SceneWindow(const std::string& windowPath) :
	EditorWindow(windowPath, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoNav)
{

}

void SceneWindow::OnGUI()
{
	EditorApplication::sceneWindowIsActive = ImGui::IsWindowFocused(ImGuiFocusedFlags_RootWindow);

	// シーンビューの描画
	auto windowSize = ImGui::GetWindowSize();
	auto sceneView = EditorApp::GetSceneView();
	// SceneWindowがアクティブでない場合は操作不可能
	auto camera = sceneView.lock()->GetSceneCamera();
	auto tagetTexture = camera.lock()->targetTexture;
	auto size = tagetTexture->GetTexelSize();
	camera.lock()->SetViewport(windowSize.x, windowSize.y);
	ImGui::Image((void*)tagetTexture->GetShaderResourceView(), ImVec2(size.x, size.y));

	auto selectGameObject = Selection::GetActiveObject();
	if (!selectGameObject.expired()) {
		float* outMatrix = selectGameObject.lock()->GetTransform().lock()->world_to_local_matrix().m16;

		//float windowWidth = (float)ImGui::GetWindowWidth();
		//float windowHeight = (float)ImGui::GetWindowHeight();
		//ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);

		//ImGuizmo::Manipulate(
		//	camera.lock()->GetViewMatrix().m[0], 
		//	camera.lock()->GetProjectionMatrix().m[0], 
		//	ImGuizmo::TRANSLATE,
		//	ImGuizmo::LOCAL, 
		//	outMatrix);

		//Matrix4x4 view = camera.lock()->GetViewMatrix();
		//Matrix4x4 projection = camera.lock()->GetProjectionMatrix();

		ImGuizmo::SetID(0);
		EditorCommand::EditTransform(camera.lock()->GetViewMatrix().m[0], camera.lock()->GetProjectionMatrix().m[0], outMatrix, true);
		ImGuizmo::IsUsing();
	}
}
#endif