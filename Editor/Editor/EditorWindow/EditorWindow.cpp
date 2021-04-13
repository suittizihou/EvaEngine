#include "EditorWindow.h"
#include <iostream>
#include <imgui_impl_dx11.h>

void EditorWindow::Init()
{
}

void EditorWindow::Update()
{
}

void EditorWindow::Draw()
{
	ImGui_ImplDX11_NewFrame();
	ImGui::NewFrame();

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
}