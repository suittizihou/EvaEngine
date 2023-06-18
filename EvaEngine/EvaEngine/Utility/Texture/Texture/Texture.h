#pragma once
#include "../../../Define/D3D11Defines.h"
#include "../../Math/Vector2/Vector2.h"
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
		Texture(const Vector2& texelSize);
		Texture(const UINT width, const UINT height);
		virtual ~Texture();

		TextureType GetTextureType() const;
		// Texture�̃T�C�Y���擾
		Vector2 GetTexelSize() const;
		// �A�X�y�N�g����擾
		Vector2 GetAspect() const;

		ID3D11ShaderResourceView* GetD3DShaderResrouceView() const;
		ID3D11SamplerState* GetD3DSamplerState() const;

	private:
		void SetD3DResource(ID3D11Resource* resource);
		void SetD3DShaderResourceView(ID3D11ShaderResourceView* shaderResourceView);

		virtual void Release();
	
	protected:
		Vector2 texelSize{ Vector2::zero() };
		TextureType textureType{ TextureType::None };

		ID3D11Resource* m_Texture{ nullptr };
		ID3D11ShaderResourceView* m_ShaderResourceView{ nullptr };
		ID3D11SamplerState* m_SamplerState{ nullptr };
	};
}