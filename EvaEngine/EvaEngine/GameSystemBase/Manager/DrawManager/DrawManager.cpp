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
		// 頂点レイアウトを設定
		DrawManager::SetVertexLayout();

		// デフォルトのシェーダーをロードする
		ShaderDataBase::Instance().LoadDefaultShader();

		// デフォルトのシェーダーをセットする
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
	// ポリゴンの生成方法の指定
	DirectX11App::g_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// DepthViewとStencilViewのクリア
	DirectX11App::g_Context->ClearDepthStencilView(
		DirectX11App::g_DepthStencilView.Get(),			// クリア対象のView
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,		// クリアフラグ
		1.0f,											// 深度クリア値
		0);												// ステンシルクリア値

		// シェーダーのセット
	Shader shader{ DrawManager::GetDefaultShader() };
	SetShader(&shader);

	// レンダーターゲットの設定
	DirectX11App::g_Context->OMSetRenderTargets(1, DirectX11App::g_RenderTargetView.GetAddressOf(), DirectX11App::g_DepthStencilView.Get());

	// 指定色で画面クリア
	float clearColor[4] = { 1.0f, 1.0f, 0.8f, 1.0f };
	// RenderTargetViewのクリア
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

	// ワールド行列
	XMStoreFloat4x4(&DirectX11App::g_ConstantBufferData.world, XMMatrixTranspose(worldMatrix));
	// ビュー行列
	DirectX::XMStoreFloat4x4(&DirectX11App::g_ConstantBufferData.view, XMMatrixTranspose(camera.lock()->GetViewMatrixDxMath()));
	// プロジェクション行列
	DirectX::XMStoreFloat4x4(&DirectX11App::g_ConstantBufferData.projection, XMMatrixTranspose(camera.lock()->GetProjectionMatrixDxMath()));
	// カメラの座標をセット
	Vector3 cameraPos = camera.lock()->GetTransform().lock()->position();
	DirectX::XMStoreFloat4(&DirectX11App::g_ConstantBufferData.cameraPos, DirectX::XMVectorSet(cameraPos.x, cameraPos.y, cameraPos.z, 0.0f));

	// メッシュ情報が格納されているMapからメッシュを取り出す
	for (const auto& meshs : model->meshes) {
		// メッシュ情報が格納された配列から１メッシュずつ取り出す
		for (auto mesh : meshs.second) {
			// インプットレイアウトの設定
			DirectX11App::g_Context->IASetInputLayout(m_InputLayout.Get());
			// 頂点バッファーの設定
			DirectX11App::g_Context->IASetVertexBuffers(0, 1, mesh.GetVertexBuffer(), &strides, &offset);
			// インデックスバッファの設定
			DirectX11App::g_Context->IASetIndexBuffer(mesh.GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);

			// マテリアルのセット
			SetMaterial(&model->materials[mesh.GetMaterialName()]);

			// 定数バッファの更新
			DirectX11App::g_Context->UpdateSubresource(DirectX11App::g_ConstantBuffer.Get(), 0, NULL, &DirectX11App::g_ConstantBufferData, 0, 0);
			// コンテキストに定数バッファを設定
			DirectX11App::g_Context->VSSetConstantBuffers(0, 1, DirectX11App::g_ConstantBuffer.GetAddressOf());
			DirectX11App::g_Context->PSSetConstantBuffers(0, 1, DirectX11App::g_ConstantBuffer.GetAddressOf());
			
			// ポリゴン描画
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

	// nullptr でない場合シェーダーをセットする
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

	// 頂点レイアウトをセット
	m_InputLayout.Attach(ShaderCompiler::CreateVertexLayout(elem, 4, "Shader/VertexShader.hlsl", "vsMain"));
}