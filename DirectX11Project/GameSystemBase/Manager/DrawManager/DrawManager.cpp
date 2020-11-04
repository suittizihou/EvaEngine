#include "DrawManager.h"
#include "../../../App/DirectX11App/DirectX11App.h"
#include "../../../Setting/Window/Window.h"
#include "../../../Utility/Material/Material.h"

void DrawManager::SetInputLayout(ID3D11InputLayout* vertexLayout)
{
	DirectX11App::g_Context->IASetInputLayout(vertexLayout);
}

void DrawManager::SetShader(const Material& material)
{
	Shader shader{ material.g_Shader };
	VertexShader vertexShader{ shader.GetVertexShader() };
	PixelShader pixelShader{ shader.GetPixelShader() };
	GeometryShader geometryShader{ shader.GetGeometryShader() };
	ComputeShader computeShader{ shader.GetComputeShader() };
	HullShader hullShader{ shader.GetHullShader() };
	DomainShader domainShader{ shader.GetDomainShader() };

	// それぞれ nullptr でない場合シェーダーをセットする
	if (computeShader != nullptr) DirectX11App::g_Context->CSSetShader(computeShader.Get(), nullptr, 0);
	if (vertexShader != nullptr) DirectX11App::g_Context->VSSetShader(vertexShader.Get(), nullptr, 0);
	if (hullShader != nullptr) DirectX11App::g_Context->HSSetShader(hullShader.Get(), nullptr, 0);
	if (domainShader != nullptr) DirectX11App::g_Context->DSSetShader(domainShader.Get(), nullptr, 0);
	if (geometryShader != nullptr) DirectX11App::g_Context->GSSetShader(geometryShader.Get(), nullptr, 0);
	if (pixelShader != nullptr) DirectX11App::g_Context->PSSetShader(pixelShader.Get(), nullptr, 0);
}

void DrawManager::SetVertexBuffer(ID3D11Buffer* vertexBuffer, UINT vertexSize)
{
	UINT offset = 0;
	DirectX11App::g_Context->IASetVertexBuffers(0, 1, &vertexBuffer, &vertexSize, &offset);
}

void DrawManager::SetIndexBuffer(ID3D11Buffer* indexBuffer)
{
	DirectX11App::g_Context->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);
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

void DrawManager::DrawEnd()
{
	DirectX11App::g_SwapChain->Present(0, 0);
}

void DrawManager::DrawIndexed(UINT vertexNum)
{
	DirectX11App::g_Context->DrawIndexed(vertexNum, 0, 0);
}
