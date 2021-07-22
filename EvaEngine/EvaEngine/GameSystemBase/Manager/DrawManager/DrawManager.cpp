#include "DrawManager.h"
#include "../../../App/DirectX11App/DirectX11App.h"
#include "../../../Setting/Window/Window.h"
#include "../../../Utility/Mesh/Mesh.h"
#include "../../../Utility/Material/Material.h"
#include "../../../Utility/Math/Vector3/Vector3.h"
#include "../../Components/Camera/Camera.h"
#include "../../Components/Transform/Transform.h"
#include "../../DataBase/ShaderDataBase/ShaderDataBase.h"

using namespace EvaEngine;
using namespace EvaEngine::Internal;

D3DInputLayout DrawManager::m_InputLayout{ nullptr };
Shader DrawManager::m_Shader{};

HRESULT DrawManager::Init()
{
	try {
		// ���_���C�A�E�g��ݒ�
		DrawManager::SetVertexLayout();

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

void DrawManager::DrawBegin()
{
	// �|���S���̐������@�̎w��
	DirectX11App::g_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// DepthView��StencilView�̃N���A
	DirectX11App::g_Context->ClearDepthStencilView(
		DirectX11App::g_DepthStencilView.Get(),			// �N���A�Ώۂ�View
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,		// �N���A�t���O
		1.0f,											// �[�x�N���A�l
		0);												// �X�e���V���N���A�l

		// �V�F�[�_�[�̃Z�b�g
	Shader shader{ DrawManager::GetDefaultShader() };
	SetShader(&shader);

	// �����_�[�^�[�Q�b�g�̐ݒ�
	DirectX11App::g_Context->OMSetRenderTargets(1, DirectX11App::g_RenderTargetView.GetAddressOf(), DirectX11App::g_DepthStencilView.Get());

	// �w��F�ŉ�ʃN���A
	float clearColor[4] = { 1.0f, 1.0f, 0.8f, 1.0f };
	// RenderTargetView�̃N���A
	DirectX11App::g_Context->ClearRenderTargetView(DirectX11App::g_RenderTargetView.Get(), clearColor);
}

void DrawManager::Draw(const std::weak_ptr<Camera>& camera, const std::weak_ptr<Transform>& transform, ModelData* model)
{
	UINT strides = sizeof(VertexData);
	UINT offset = 0;

	Matrix4x4 matrix = transform.lock()->local_to_world_matrix();
	DirectX::XMMATRIX worldMatrix
	{
		matrix.m[0][0], matrix.m[0][1], matrix.m[0][2], matrix.m[0][3],
		matrix.m[1][0], matrix.m[1][1], matrix.m[1][2], matrix.m[1][3],
		matrix.m[2][0], matrix.m[2][1], matrix.m[2][2], matrix.m[2][3],
		matrix.m[3][0], matrix.m[3][1], matrix.m[3][2], matrix.m[3][3]
	};

	// ���[���h�s��
	XMStoreFloat4x4(&DirectX11App::g_ConstantBufferData.world, XMMatrixTranspose(worldMatrix));
	// �r���[�s��
	DirectX::XMStoreFloat4x4(&DirectX11App::g_ConstantBufferData.view, XMMatrixTranspose(camera.lock()->GetViewMatrixDxMath()));
	// �v���W�F�N�V�����s��
	DirectX::XMStoreFloat4x4(&DirectX11App::g_ConstantBufferData.projection, XMMatrixTranspose(camera.lock()->GetProjectionMatrixDxMath()));
	// �J�����̍��W���Z�b�g
	Vector3 cameraPos = camera.lock()->GetTransform().lock()->position();
	DirectX::XMStoreFloat4(&DirectX11App::g_ConstantBufferData.cameraPos, DirectX::XMVectorSet(cameraPos.x, cameraPos.y, cameraPos.z, 0.0f));

	// ���b�V����񂪊i�[����Ă���Map���烁�b�V�������o��
	for (const auto& meshs : model->meshes) {
		// ���b�V����񂪊i�[���ꂽ�z�񂩂�P���b�V�������o��
		for (auto mesh : meshs.second) {
			// �C���v�b�g���C�A�E�g�̐ݒ�
			DirectX11App::g_Context->IASetInputLayout(m_InputLayout.Get());
			// ���_�o�b�t�@�[�̐ݒ�
			DirectX11App::g_Context->IASetVertexBuffers(0, 1, mesh.GetVertexBuffer(), &strides, &offset);
			// �C���f�b�N�X�o�b�t�@�̐ݒ�
			DirectX11App::g_Context->IASetIndexBuffer(mesh.GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);

			// �}�e���A���̃Z�b�g
			SetMaterial(&model->materials[mesh.GetMaterialName()]);

			// �萔�o�b�t�@�̍X�V
			DirectX11App::g_Context->UpdateSubresource(DirectX11App::g_ConstantBuffer.Get(), 0, NULL, &DirectX11App::g_ConstantBufferData, 0, 0);
			// �R���e�L�X�g�ɒ萔�o�b�t�@��ݒ�
			DirectX11App::g_Context->VSSetConstantBuffers(0, 1, DirectX11App::g_ConstantBuffer.GetAddressOf());
			DirectX11App::g_Context->PSSetConstantBuffers(0, 1, DirectX11App::g_ConstantBuffer.GetAddressOf());
			
			// �|���S���`��
			DirectX11App::g_Context->DrawIndexed(static_cast<UINT>(mesh.GetIndices().size()), 0, 0);
		}
	}
}

void DrawManager::DrawEnd()
{
	DirectX11App::g_SwapChain->Present(1, 0);
}

void DrawManager::SetMaterial(Material* material)
{
	DirectX11App::g_ConstantBufferData.materialDiffuse = material->diffuse;
	DirectX11App::g_ConstantBufferData.materialAmbient = material->ambient;
	DirectX11App::g_ConstantBufferData.materialSpecular = material->specular;

	SetShader(material);
}

void DrawManager::SetShader(Shader* shader) {

	// nullptr �łȂ��ꍇ�V�F�[�_�[���Z�b�g����
	if (shader->GetComputeShader() != nullptr) DirectX11App::g_Context->CSSetShader(shader->GetComputeShader(), nullptr, 0);
	if (shader->GetVertexShader() != nullptr) DirectX11App::g_Context->VSSetShader(shader->GetVertexShader(), nullptr, 0);
	if (shader->GetHullShader() != nullptr) DirectX11App::g_Context->HSSetShader(shader->GetHullShader(), nullptr, 0);
	if (shader->GetDomainShader() != nullptr) DirectX11App::g_Context->DSSetShader(shader->GetDomainShader(), nullptr, 0);
	if (shader->GetGeometryShader() != nullptr) DirectX11App::g_Context->GSSetShader(shader->GetGeometryShader(), nullptr, 0);
	if (shader->GetPixelShader() != nullptr) DirectX11App::g_Context->PSSetShader(shader->GetPixelShader(), nullptr, 0);
}

void DrawManager::SetShader(Material* material)
{
	SetShader(&material->g_Shader);
}

EvaEngine::Shader DrawManager::GetDefaultShader()
{
	return m_Shader;
}

void DrawManager::SetVertexLayout()
{
	D3D11_INPUT_ELEMENT_DESC elem[] = {
	{ "POSITION",   0, DXGI_FORMAT_R32G32B32_FLOAT,     0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",     0, DXGI_FORMAT_R32G32B32_FLOAT,     0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{ "COLOR",      0, DXGI_FORMAT_R32G32B32A32_FLOAT,  0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{ "TEXCOORD",   0, DXGI_FORMAT_R32G32_FLOAT,        0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};

	// ���_���C�A�E�g���Z�b�g
	m_InputLayout.Attach(ShaderCompiler::CreateVertexLayout(elem, 4, "Shader/VertexShader.hlsl", "vsMain"));
}