#pragma once

#include <memory>
#include "../Texture/Texture.h"

namespace EvaEngine {
	class Texture2D;

	class RenderTexture : public Texture {
	public:
		RenderTexture(const UINT width, const UINT height);
	public:
		void Create();
		
	public:
		void SetRenderTarget(const Color& clearColor) const;

		ID3D11ShaderResourceView* GetShaderResourceView() const;

	private:
		std::shared_ptr<Texture2D> m_pTexture2D{ nullptr };
		Internal::D3DRenderTargetView m_RenderTargetView{ nullptr };
		Internal::D3DDepthStencilView m_DepthStencilView{ nullptr };
		Internal::D3DShaderResourceView m_ShaderResourceView{ nullptr };
		Internal::D3DSamplerState m_SamplerState{ nullptr };
	};
}