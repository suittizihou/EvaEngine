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
		std::unique_ptr<Texture2D> m_pTexture2D{ nullptr };
		ID3D11RenderTargetView* m_RenderTargetView{ nullptr };
		ID3D11DepthStencilView* m_DepthStencilView{ nullptr };
	};
}