#pragma once

#include "../Texture/Texture.h"

#undef LoadImage

namespace EvaEngine {

	class Texture2D : public Texture {
	public:
		Texture2D(const UINT width, const UINT height);
		Texture2D(const UINT width, const UINT height, const DXGI_FORMAT& textureFormat);
		Texture2D(const UINT width, const UINT height, const D3D11_TEXTURE2D_DESC& textureDesc);
		~Texture2D();


	private:
		void Init();

	public:
		void Create() override;

		void STDMETHODCALLTYPE GetD3DTexture2DDESC(_Out_ D3D11_TEXTURE2D_DESC* pDesc);
		ID3D11Texture2D* GetD3DTexture2D() const;


	private:
		void CreateTex2D(const DXGI_FORMAT& format);
		void CreateShaderResourceView(const DXGI_FORMAT& format);
		void CreateSamplerState(const DXGI_FORMAT& format);

	private:
		// 2�����e�N�X�`���̐ݒ�
		D3D11_TEXTURE2D_DESC m_TextureDesc{};
	};
}