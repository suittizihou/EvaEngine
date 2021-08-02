#include "GameWindow.h"
#include "../../../GameSystemBase/Components/Camera/Camera.h"
#include "../../../Utility/Texture/RenderTexture/RenderTexture.h"

void EvaEngine::Editor::Internal::GameWindow::Init()
{
	windowFlags |= ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoNav;
}

void EvaEngine::Editor::Internal::GameWindow::OnGUI()
{
	auto windowSize = ImGui::GetWindowSize();

	// �S�J���������擾���A�e�N�X�`���Ƃ���GameWindow�ɕ`��
	auto cameras = Camera::GetAllCamera();
	// �P����n�܂��Ă���̂́A0�Ԗڂ̗v�f�͕K��SceneView�̂���
	for (int i = 1; i < cameras.size(); ++i) {
		auto tagetTexture = cameras[i].lock()->targetTexture;
		auto size = tagetTexture->GetTexelSize();
		cameras[i].lock()->SetViewport(size.x, size.y);
		// �A�X�y�N�g���ۂ�
		windowSize.y = windowSize.x / size.x * size.y;
		ImGui::Image((void*)tagetTexture->GetShaderResourceView(), ImVec2(windowSize.x, windowSize.y));
	}
}