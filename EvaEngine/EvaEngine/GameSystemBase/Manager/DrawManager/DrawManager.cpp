#include "DrawManager.h"
#include "../../../App/DirectX11App/DirectX11App.h"
#include "../../../Setting/Window/Window.h"
#include "../../../Utility/Mesh/Mesh.h"
#include "../../../Utility/Material/Material.h"
#include "../../../Utility/Math/Vector3/Vector3.h"
#include "../../../Utility/Texture/RenderTexture/RenderTexture.h"
#include "../../../Utility/ShaderUtility/ShaderBase/ShaderBase.h"
#include "../../Components/Camera/Camera.h"
#include "../../Components/Transform/Transform.h"
#include "../../DataBase/ShaderDataBase/ShaderDataBase.h"

//#include <chrono>

using namespace EvaEngine;
using namespace EvaEngine::Internal;

Shader DrawManager::m_Shader{};

HRESULT DrawManager::Init()
{
	try {
		// �f�t�H���g�̃V�F�[�_�[�����[�h����
		ShaderDataBase::Instance().LoadDefaultShader();

		// �f�t�H���g�̃V�F�[�_�[���Z�b�g����
		m_Shader.SetVertexShader(ShaderDataBase::Instance().GetDefaultVertexShader());
		m_Shader.SetPixelShader(ShaderDataBase::Instance().GetDefaultPixelShader());

		return S_OK;
	}
	catch (std::string error) {
		return E_ABORT;
	}
}

void DrawManager::DrawBegin(const std::weak_ptr<Camera>& camera)
{
	//// DepthView��StencilView�̃N���A
	//DirectX11App::g_Context->ClearDepthStencilView(
	//	DirectX11App::g_EditorDepthStencilView.Get(),	// �N���A�Ώۂ�View
	//	D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,		// �N���A�t���O
	//	1.0f,											// �[�x�N���A�l
	//	0);												// �X�e���V���N���A�l

	//	// �V�F�[�_�[�̃Z�b�g
	//Shader shader{ DrawManager::GetDefaultShader() };
	//SetShader(&shader);

	//// �����_�[�^�[�Q�b�g�̐ݒ�
	//DirectX11App::g_Context->OMSetRenderTargets(1, DirectX11App::g_EditorRenderTargetView.GetAddressOf(), DirectX11App::g_EditorDepthStencilView.Get());

	//// �w��F�ŉ�ʃN���A
	//float clearColor[4] = { 1.0f, 1.0f, 0.8f, 1.0f };
	//// RenderTargetView�̃N���A
	//DirectX11App::g_Context->ClearRenderTargetView(DirectX11App::g_EditorRenderTargetView.Get(), clearColor);

	//camera.lock()->SetRenderTarget();
}

void DrawManager::Draw(const std::weak_ptr<Camera>& camera, const std::weak_ptr<Transform>& transform, const std::weak_ptr<ModelData>& model)
{
	//std::chrono::system_clock::time_point start, end;
	//start = std::chrono::system_clock::now();
	UINT strides = sizeof(VertexData);
	UINT offset = 0;

	// ���[���h�s��
	DirectX11App::g_ConstantBufferData.world = transform.lock()->local_to_world_matrix().transpose();

	auto context = DirectX11App::g_Context;

	// ���b�V����񂪊i�[����Ă���Map���烁�b�V�������o��
	for (const auto& meshs : model.lock()->meshes) {
		// ���b�V����񂪊i�[���ꂽ�z�񂩂�P���b�V�������o��
		for (auto mesh : meshs.second) {
			// �C���v�b�g���C�A�E�g�̐ݒ�
			context->IASetInputLayout(ShaderDataBase::Instance().GetDefaultVertexShader().m_pInputLayout);
			// ���_�o�b�t�@�[�̐ݒ�
			context->IASetVertexBuffers(0, 1, mesh.GetVertexBuffer(), &strides, &offset);
			// �C���f�b�N�X�o�b�t�@�̐ݒ�
			context->IASetIndexBuffer(mesh.GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);

			// �}�e���A���̃Z�b�g
			//SetMaterial(&model.lock()->materials[mesh.GetMaterialName()]);

			// �萔�o�b�t�@�̍X�V
			context->UpdateSubresource(DirectX11App::g_ConstantBuffer, 0, NULL, &DirectX11App::g_ConstantBufferData, 0, 0);
			// �R���e�L�X�g�ɒ萔�o�b�t�@��ݒ�
			context->VSSetConstantBuffers(0, 1, &DirectX11App::g_ConstantBuffer);
			context->PSSetConstantBuffers(0, 1, &DirectX11App::g_ConstantBuffer);
			
			// �|���S���`��
			context->DrawIndexed(static_cast<UINT>(mesh.GetIndices().size()), 0, 0);
		}
	}
	//end = std::chrono::system_clock::now();
	//double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

void DrawManager::DrawEnd()
{	
	DirectX11App::g_SwapChain->Present(1, 0);
}

void DrawManager::SetMaterial(Material* material)
{
	//DirectX11App::g_ConstantBufferData.materialDiffuse = material->diffuse;
	//DirectX11App::g_ConstantBufferData.materialAmbient = material->ambient;
	//DirectX11App::g_ConstantBufferData.materialSpecular = material->specular;

	SetShader(material);
}

void DrawManager::SetShader(Shader* shader) {

	// nullptr �łȂ��ꍇ�V�F�[�_�[���Z�b�g����
	if (shader->GetComputeShader().m_pShader != nullptr) DirectX11App::g_Context->CSSetShader(shader->GetComputeShader().m_pShader, nullptr, 0);
	if (shader->GetVertexShader().m_pShader != nullptr) DirectX11App::g_Context->VSSetShader(shader->GetVertexShader().m_pShader, nullptr, 0);
	if (shader->GetHullShader().m_pShader != nullptr) DirectX11App::g_Context->HSSetShader(shader->GetHullShader().m_pShader, nullptr, 0);
	if (shader->GetDomainShader().m_pShader != nullptr) DirectX11App::g_Context->DSSetShader(shader->GetDomainShader().m_pShader, nullptr, 0);
	if (shader->GetGeometryShader().m_pShader != nullptr) DirectX11App::g_Context->GSSetShader(shader->GetGeometryShader().m_pShader, nullptr, 0);
	if (shader->GetPixelShader().m_pShader != nullptr) DirectX11App::g_Context->PSSetShader(shader->GetPixelShader().m_pShader, nullptr, 0);
}

void DrawManager::SetShader(Material* material)
{
	SetShader(&material->g_Shader);
}

EvaEngine::Shader DrawManager::GetDefaultShader()
{
	return m_Shader;
}