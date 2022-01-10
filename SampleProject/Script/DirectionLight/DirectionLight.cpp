#include "DirectionLight.h"

void DirectionLight::Update()
{
	// ���z���̌����ύX
	auto euler = GetTransform().lock()->rotation().euler_angles();
	euler.normalize();
	DirectX::XMStoreFloat3(&EvaEngine::Internal::DirectX11App::g_ConstantBufferData.lightDirection, euler);
	DirectX::XMStoreFloat3(&EvaEngine::Internal::DirectX11App::g_ConstantBufferData.lightColor, m_LightColor);
	DirectX::XMStoreFloat3(&EvaEngine::Internal::DirectX11App::g_ConstantBufferData.materialAmbient, m_AmbientColor);
}

#if _DEBUG
void DirectionLight::OnGUI()
{
	// ���z���̃J���[�ݒ�
	ImGui::ColorPicker3("LightColor", m_LightColor.v);

	// �A���r�G���g�F
	ImGui::ColorPicker3("Ambient", m_AmbientColor.v);

	// ���z���Ɋ֌W�Ȃ����ǃe�J����̒���
	ImGui::DragFloat("Shine", &EvaEngine::Internal::DirectX11App::g_ConstantBufferData.shine, 0.05f, -FLT_MAX, +FLT_MAX);
}
#endif