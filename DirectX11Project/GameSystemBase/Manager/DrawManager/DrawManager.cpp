#include "DrawManager.h"
#include "../../../App/DirectX11App/DirectX11App.h"
#include "../../../Setting/Window/Window.h"
#include "../../../Utility/Material/Material.h"

InputLayout DrawManager::m_InputLayout{ nullptr };

void DrawManager::SetShader(const My3DLib::Material& material)
{
	Shader shader{ material.g_Shader };
	ID3D11VertexShader* vertexShader{ shader.GetVertexShader() };
	ID3D11PixelShader* pixelShader{ shader.GetPixelShader() };
	ID3D11GeometryShader* geometryShader{ shader.GetGeometryShader() };
	ID3D11ComputeShader* computeShader{ shader.GetComputeShader() };
	ID3D11HullShader* hullShader{ shader.GetHullShader() };
	ID3D11DomainShader* domainShader{ shader.GetDomainShader() };

	// それぞれ nullptr でない場合シェーダーをセットする
	if (computeShader != nullptr) DirectX11App::g_Context->CSSetShader(computeShader, nullptr, 0);
	if (vertexShader != nullptr) DirectX11App::g_Context->VSSetShader(vertexShader, nullptr, 0);
	if (hullShader != nullptr) DirectX11App::g_Context->HSSetShader(hullShader, nullptr, 0);
	if (domainShader != nullptr) DirectX11App::g_Context->DSSetShader(domainShader, nullptr, 0);
	if (geometryShader != nullptr) DirectX11App::g_Context->GSSetShader(geometryShader, nullptr, 0);
	if (pixelShader != nullptr) DirectX11App::g_Context->PSSetShader(pixelShader, nullptr, 0);
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

void DrawManager::Draw(const My3DLib::ModelData::Model& model)
{
	My3DLib::Material material{};
	material.g_Shader.SetVertexShader(0);
	material.g_Shader.SetPixelShader(0);

	UINT strides = sizeof(My3DLib::VertexData);
	UINT offset = 0;

	// シェーダーのセット
	DrawManager::SetShader(material);

	for (const auto& meshs : model.meshes) {
		for (auto mesh : meshs.second) {
			// インプットレイアウトの設定
			DirectX11App::g_Context->IASetInputLayout(m_InputLayout.Get());
			// 頂点バッファーの設定
			DirectX11App::g_Context->IASetVertexBuffers(0, 1, mesh.GetVertexBuffer(), &strides, &offset);
			// インデックスバッファの設定
			DirectX11App::g_Context->IASetIndexBuffer(mesh.GetIndexBuffer(), DXGI_FORMAT_R32_UINT, 0);
			// ポリゴンの種類
			DirectX11App::g_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			// レンダーターゲットの設定
			DirectX11App::g_Context->OMSetRenderTargets(1, DirectX11App::g_RenderTargetView.GetAddressOf(), DirectX11App::g_DepthStencilView.Get());

			// ポリゴン描画
			DirectX11App::g_Context->DrawIndexed(static_cast<UINT>(mesh.GetVertices().size()), 0, 0);
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