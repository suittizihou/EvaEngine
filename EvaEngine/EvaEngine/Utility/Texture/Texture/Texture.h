#pragma once
#include "../../../Define/D3D11Defines.h"
#include "../../Math/Vector2Int/Vector2Int.h"
#include "../../Math/Color/Color.h"

namespace EvaEngine {
	class TextureManager;

	class Texture {
		friend EvaEngine::TextureManager;

	public:
		enum class TextureType {
			None,
			Tex2D,
			Tex3D
		};

	public:
		Texture(const Vector2Int& texelSize);
		Texture(const int width, const int height);
		virtual ~Texture();

		TextureType GetTextureType() const;
		// Textureのサイズを取得
		Vector2Int GetTexelSize() const;
		// アスペクト比を取得
		Vector2Int GetAspect() const;

		ID3D11ShaderResourceView* GetD3DShaderResrouceView() const;
		ID3D11SamplerState* GetD3DSamplerState() const;

	private:
		void SetD3DResource(ID3D11Resource* resource);
		void SetD3DShaderResourceView(ID3D11ShaderResourceView* shaderResourceView);

		virtual void Release();
	
	protected:
		Vector2Int texelSize{ Vector2Int::zero() };
		TextureType textureType{ TextureType::None };

		ID3D11Resource* m_Texture{ nullptr };
		ID3D11ShaderResourceView* m_ShaderResourceView{ nullptr };
		ID3D11SamplerState* m_SamplerState{ nullptr };
	};
}