#include "DirectionLight.h"

void DirectionLight::Update()
{
	// 太陽光の向き変更
	auto forward = GetTransform().lock()->forward();
	forward.normalize();
	EvaEngine::Internal::DirectX11App::g_ConstantBufferData.lightDirection = forward;
	EvaEngine::Internal::DirectX11App::g_ConstantBufferData.lightColor = m_LightColor;
	EvaEngine::Internal::DirectX11App::g_ConstantBufferData.materialAmbient = m_AmbientColor;
}

#if _DEBUG
void DirectionLight::OnGUI()
{
	// 太陽光のカラー設定
	ImGui::ColorPicker3("LightColor", m_LightColor.v);

	// アンビエント色
	ImGui::ColorPicker3("Ambient", m_AmbientColor.v);

	// 太陽光に関係ないけどテカリ具合の調節
	ImGui::DragFloat("Shine", &EvaEngine::Internal::DirectX11App::g_ConstantBufferData.shine, 0.05f, -FLT_MAX, +FLT_MAX);
}
#endif