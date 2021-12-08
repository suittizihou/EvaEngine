#pragma once
#include "../../../Define/D3D11Defines.h"
#include "../../Math/Vector2/Vector2.h"
#include "../../Math/Color/Color.h"

namespace EvaEngine {
	class Texture {
	public:
		enum class TextureType {
			None,
			Tex2D,
			Tex3D
		};

	public:
		Texture(const UINT width, const UINT height);
		virtual ~Texture() = default;

		TextureType GetTextureType() const;
		// Textureのサイズを取得
		Vector2 GetTexelSize() const;
		// アスペクト比を取得
		Vector2 GetAspect() const;

		ID3D11ShaderResourceView* GetD3DShaderResrouceView() const;
		ID3D11SamplerState* GetD3DSamplerState() const;

	protected:
		void CreateShaderResourceView(const ID3D11Resource& resource,const D3D11_SHADER_RESOURCE_VIEW_DESC& desc);
		void CreateSamplerState(const D3D11_SAMPLER_DESC& desc);

	protected:
		Vector2 texelSize{ Vector2::zero() };
		TextureType textureType{ TextureType::None };

		ID3D11Resource* m_Texture{ nullptr };
		ID3D11ShaderResourceView* m_ShaderResourceView{ nullptr };
		ID3D11SamplerState* m_SamplerState{ nullptr };
	};
}