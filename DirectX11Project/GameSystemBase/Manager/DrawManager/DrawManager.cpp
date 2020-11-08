#include "DrawManager.h"
#include "../../../App/DirectX11App/DirectX11App.h"
#include "../../../Setting/Window/Window.h"
#include "../../../Utility/Material/Material.h"
#include "../../../Utility/Math/Vector3/Vector3.h"

InputLayout DrawManager::m_InputLayout{ nullptr };

void DrawManager::SetShader(Shader& shader) {
	// nullptr でない場合シェーダーをセットする
	if (shader.GetComputeShader() != nullptr) DirectX11App::g_Context->CSSetShader(shader.GetComputeShader(), nullptr, 0);
	if (shader.GetVertexShader() != nullptr) DirectX11App::g_Context->VSSetShader(shader.GetVertexShader(), nullptr, 0);
	if (shader.GetHullShader() != nullptr) DirectX11App::g_Context->HSSetShader(shader.GetHullShader(), nullptr, 0);
	if (shader.GetDomainShader() != nullptr) DirectX11App::g_Context->DSSetShader(shader.GetDomainShader(), nullptr, 0);
	if (shader.GetGeometryShader() != nullptr) DirectX11App::g_Context->GSSetShader(shader.GetGeometryShader(), nullptr, 0);
	if (shader.GetPixelShader() != nullptr) DirectX11App::g_Context->PSSetShader(shader.GetPixelShader(), nullptr, 0);
}

void DrawManager::SetShader(My3DLib::Material& material)
{
	SetShader(material.g_Shader);
}

void DrawManager::DrawBegin()
{
	// ポリゴンの生成方法の指定
	DirectX11App::g_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// 指定色で画面クリア
	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

	// RenderTargetViewのクリア
	DirectX11App::g_Context->ClearRenderTargetView(DirectX11App::g_RenderTargetView.Get(), clearColor);

	// DepthViewとStencilViewのクリア
	DirectX11App::g_Context->ClearDepthStencilView(
		DirectX11App::g_DepthStencilView.Get(),			// クリア対象のView
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,		// クリアフラグ
		1.0f,											// 深度クリア値
		0);												// ステンシルクリア値
}

void DrawManager::Draw(const My3DLib::Model& model)
{
	Shader shader{};
	shader.SetVertexShader(0);
	shader.SetPixelShader(0);

	// ポリゴンの種類
	DirectX11App::g_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	// シェーダーのセット
	DrawManager::SetShader(shader);
	// レンダーターゲットの設定
	DirectX11App::g_Context->OMSetRenderTargets(1, DirectX11App::g_RenderTargetView.GetAddressOf(), DirectX11App::g_DepthStencilView.Get());

	UINT strides = sizeof(My3DLib::VertexData);
	UINT offset = 0;

	Vector3 pos = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 degree = Vector3(0.0f, 180.0f, 0.0f);
	Vector3 scale = Vector3(1.0f, 1.0f, 1.0f);

	for (const auto& meshs : model.meshes) {
		for (auto mesh : meshs.second) {
			// インプットレイアウトの設定
			DirectX11App::g_Context->IASetInputLayout(m_InputLayout.Get());
			// 頂点バッファーの設定
			DirectX11App::g_Context->IASetVertexBuffers(0, 1, mesh.GetVertexBuffer(), &strides, &offset);
			// インデックスバッファの設定
			DirectX11App::g_Context->IASetIndexBuffer(mesh.GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);

			//// ワールド行列の設定
			//DirectX::XMMATRIX world_matrix;
			//DirectX::XMMATRIX translate = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
			//DirectX::XMMATRIX rotate_x = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(degree.x));
			//DirectX::XMMATRIX rotate_y = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(degree.y));
			//DirectX::XMMATRIX rotate_z = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(degree.z));
			//DirectX::XMMATRIX scale_mat = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
			//world_matrix = scale_mat * rotate_x * rotate_y * rotate_z * translate;

			//// ワールド行列を定数バッファに設定
			//DirectX::XMStoreFloat4x4(&DirectX11App::g_ConstantBufferData.world, DirectX::XMMatrixTranspose(world_matrix));
			//// 定数バッファの更新
			//DirectX11App::g_Context->UpdateSubresource(DirectX11App::g_ConstantBuffer.Get(), 0, NULL, &DirectX11App::g_ConstantBufferData, 0, 0);

			//ID3D11Buffer* buffer = DirectX11App::g_ConstantBuffer.Get();
			//// コンテキストに定数バッファを設定
			//DirectX11App::g_Context->VSSetConstantBuffers(0, 1, &buffer);
			//DirectX11App::g_Context->PSSetConstantBuffers(0, 1, &buffer);

			// ポリゴン描画
			DirectX11App::g_Context->DrawIndexed(static_cast<UINT>(mesh.GetIndices().size()), 0, 0);
		}
	}
}

void DrawManager::DrawEnd()
{
	DirectX11App::g_SwapChain->Present(0, 0);
}

void DrawManager::SetInputLayout(ID3D11InputLayout* inputLayout)
{
	m_InputLayout.Attach(inputLayout);
}