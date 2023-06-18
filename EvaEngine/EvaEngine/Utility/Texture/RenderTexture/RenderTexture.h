#pragma once

#include <memory>
#include "../Texture/Texture.h"

namespace EvaEngine {
	class Texture2D;

	class RenderTexture : public Texture {
	public:
		RenderTexture(const UINT width, const UINT height);
		~RenderTexture();
	public:
		void Create();
		void Release();

	public:
		void SetRenderTarget(const Color& clearColor) const;

		ID3D11ShaderResourceView* GetShaderResourceView() const;

	private:
		void CreateTex2D(const DXGI_FORMAT& format);
		//void CreateTex3D();
		void CreateRenderTargetView(const DXGI_FORMAT& format);
		void CreateShaderResourceView(const DXGI_FORMAT& format);
		void CreateDepthStencilView();
		void CreateSamplerState();;

	private:
		ID3D11RenderTargetView* m_RenderTargetView{ nullptr };
		ID3D11DepthStencilView* m_DepthStencilView{ nullptr };
	};
}