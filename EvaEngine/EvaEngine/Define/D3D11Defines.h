#pragma once

#include <wrl.h>
#include <d3d11.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

namespace EvaEngine {
	namespace Internal {
		typedef Microsoft::WRL::ComPtr<ID3D11Device> D3DDevice;
		typedef Microsoft::WRL::ComPtr<ID3D11DeviceContext> D3DContext;
		typedef Microsoft::WRL::ComPtr<IDXGISwapChain> SwapChain;
		typedef Microsoft::WRL::ComPtr<ID3D11RenderTargetView> RenderTargetView;
		typedef Microsoft::WRL::ComPtr<ID3D11Buffer> ConstantBuffer, VertexBuffer, IndexBuffer, StructuredBuffer;
		typedef Microsoft::WRL::ComPtr<ID3D11InputLayout> InputLayout;
		typedef Microsoft::WRL::ComPtr<ID3D11VertexShader> VertexShader;
		typedef Microsoft::WRL::ComPtr<ID3D11GeometryShader> GeometryShader;
		typedef Microsoft::WRL::ComPtr<ID3D11PixelShader> PixelShader;
		typedef Microsoft::WRL::ComPtr<ID3D11ComputeShader> ComputeShader;
		typedef Microsoft::WRL::ComPtr<ID3D11HullShader> HullShader;
		typedef Microsoft::WRL::ComPtr<ID3D11DomainShader> DomainShader;
		typedef Microsoft::WRL::ComPtr<ID3DBlob> D3DBlob;
		typedef Microsoft::WRL::ComPtr<ID3D11Texture2D> Texture2D;
		typedef Microsoft::WRL::ComPtr<ID3D11DepthStencilView> DepthStencilView;
		typedef Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> ShaderTexture;
		typedef Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> ComputeOutputView;
	}
}