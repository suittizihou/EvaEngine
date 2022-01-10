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

void DrawManager::DrawBegin(const std::weak_ptr<Camera>& camera)
{
	//// DepthViewとStencilViewのクリア
	//DirectX11App::g_Context->ClearDepthStencilView(
	//	DirectX11App::g_EditorDepthStencilView.Get(),	// クリア対象のView
	//	D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,		// クリアフラグ
	//	1.0f,											// 深度クリア値
	//	0);												// ステンシルクリア値

	//	// シェーダーのセット
	//Shader shader{ DrawManager::GetDefaultShader() };
	//SetShader(&shader);

	//// レンダーターゲットの設定
	//DirectX11App::g_Context->OMSetRenderTargets(1, DirectX11App::g_EditorRenderTargetView.GetAddressOf(), DirectX11App::g_EditorDepthStencilView.Get());

	//// 指定色で画面クリア
	//float clearColor[4] = { 1.0f, 1.0f, 0.8f, 1.0f };
	//// RenderTargetViewのクリア
	//DirectX11App::g_Context->ClearRenderTargetView(DirectX11App::g_EditorRenderTargetView.Get(), clearColor);

	//camera.lock()->SetRenderTarget();
}

void DrawManager::Draw(const std::weak_ptr<Camera>& camera, const std::weak_ptr<Transform>& transform, const std::weak_ptr<ModelData>& model)
{
	//std::chrono::system_clock::time_point start, end;
	//start = std::chrono::system_clock::now();
	UINT strides = sizeof(VertexData);
	UINT offset = 0;

	// ワールド行列
	XMStoreFloat4x4(&DirectX11App::g_ConstantBufferData.world, DirectX::XMMatrixTranspose(transform.lock()->local_to_world_matrix()));

	// メッシュ情報が格納されているMapからメッシュを取り出す
	for (const auto& meshs : model.lock()->meshes) {
		// メッシュ情報が格納された配列から１メッシュずつ取り出す
		for (auto mesh : meshs.second) {
			// インプットレイアウトの設定
			DirectX11App::g_Context->IASetInputLayout(ShaderDataBase::Instance().GetDefaultVertexShader().m_pInputLayout);
			// 頂点バッファーの設定
			DirectX11App::g_Context->IASetVertexBuffers(0, 1, mesh.GetVertexBuffer(), &strides, &offset);
			// インデックスバッファの設定
			DirectX11App::g_Context->IASetIndexBuffer(mesh.GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);

			// マテリアルのセット
			//SetMaterial(&model.lock()->materials[mesh.GetMaterialName()]);

			// 定数バッファの更新
			DirectX11App::g_Context->UpdateSubresource(DirectX11App::g_ConstantBuffer, 0, NULL, &DirectX11App::g_ConstantBufferData, 0, 0);
			// コンテキストに定数バッファを設定
			DirectX11App::g_Context->VSSetConstantBuffers(0, 1, &DirectX11App::g_ConstantBuffer);
			DirectX11App::g_Context->PSSetConstantBuffers(0, 1, &DirectX11App::g_ConstantBuffer);
			
			// ポリゴン描画
			DirectX11App::g_Context->DrawIndexed(static_cast<UINT>(mesh.GetIndices().size()), 0, 0);
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

	// nullptr でない場合シェーダーをセットする
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