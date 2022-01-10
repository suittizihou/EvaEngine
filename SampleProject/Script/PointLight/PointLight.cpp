#include "PointLight.h"

void PointLight::Update()
{
	auto pos = GetTransform().lock()->position();
	DirectX::XMStoreFloat3(&EvaEngine::Internal::DirectX11App::g_ConstantBufferData.ptPosition, pos);
	EvaEngine::Internal::DirectX11App::g_ConstantBufferData.ptRange = m_Range;
	DirectX::XMStoreFloat3(&EvaEngine::Internal::DirectX11App::g_ConstantBufferData.ptColor, m_Color);
}

#if _DEBUG
void PointLight::OnGUI() {
	ImGui::DragFloat("Range", &m_Range, 0.05f, 0.0f, FLT_MAX);
	ImGui::ColorPicker3("Color", m_Color.v);
}
#endif