#if _DEBUG
#include <imgui.h>
#include <backends/imgui_impl_win32.h>
#include <backends/imgui_impl_dx11.h>
#include <ImGuizmo.h>

#include "EditorCommand.h"
#include "../EvaEngine/Utility/Math/Math.h"

using namespace EvaEngine::Editor::Internal;

ImGuizmo::OPERATION EditorCommand::mCurrentGizmoOperation{ ImGuizmo::TRANSLATE };

void EditorCommand::EditTransform(float* cameraView, float* cameraProjection, float* matrix, bool editTransformDecomposition, float camDistance)
{
	static ImGuizmo::OPERATION mCurrentGizmoOperation(ImGuizmo::TRANSLATE);
	static ImGuizmo::MODE mCurrentGizmoMode(ImGuizmo::LOCAL);
	static bool useSnap = false;
	static float snap[3] = { 1.f, 1.f, 1.f };
	static float bounds[] = { -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f };
	static float boundsSnap[] = { 0.1f, 0.1f, 0.1f };
	static bool boundSizing = false;
	static bool boundSizingSnap = false;

	float windowWidth = (float)ImGui::GetWindowWidth();
	float windowHeight = (float)ImGui::GetWindowHeight();
	ImVec2 vec = ImGui::GetWindowPos();
	ImGuizmo::SetRect(vec.x, vec.y, windowWidth, windowHeight);
	ImGuizmo::Manipulate(cameraView, cameraProjection, mCurrentGizmoOperation, mCurrentGizmoMode, matrix, NULL, useSnap ? &snap[0] : NULL, boundSizing ? bounds : NULL, boundSizingSnap ? boundsSnap : NULL);
}

#endif