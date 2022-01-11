#include "SpotLight.h"

using namespace EvaEngine;
using namespace EvaEngine::Internal;

void SpotLight::Update()
{
	auto transform = GetTransform().lock();
	DirectX11App::g_ConstantBufferData.spPosition = transform->position();
	DirectX11App::g_ConstantBufferData.spDirection = transform->forward();
	DirectX11App::g_ConstantBufferData.spColor = m_Color;
	DirectX11App::g_ConstantBufferData.spRange = m_Range;
	DirectX11App::g_ConstantBufferData.spAngle = m_Angle * Mathf::deg_to_rad();
}

void SpotLight::OnGUI()
{
	ImGui::ColorPicker3("Color", m_Color.v);
	ImGui::DragFloat("Range", &m_Range, 0.05f, 0.0f, FLT_MAX);
	ImGui::DragFloat("Angle", &m_Angle, 0.05f, 0.0f, FLT_MAX);
}