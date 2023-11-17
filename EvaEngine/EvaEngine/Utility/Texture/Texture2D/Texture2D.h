#pragma once

#include "../Texture/Texture.h"

#undef LoadImage

namespace EvaEngine {

	class Texture2D : public Texture {
	public:
		Texture2D(const Vector2Int& texelSize);
		Texture2D(const Vector2Int& texelSize, const DXGI_FORMAT& textureFormat);
		Texture2D(const Vector2Int& texelSize, const D3D11_TEXTURE2D_DESC& textureDesc);
		Texture2D(const int width, const int height);
		Texture2D(const int width, const int height, const DXGI_FORMAT& textureFormat);
		Texture2D(const int width, const int height, const D3D11_TEXTURE2D_DESC& textureDesc);
		~Texture2D();

	public:
		//void Apply();
		void STDMETHODCALLTYPE GetD3DTexture2DDESC(_Out_ D3D11_TEXTURE2D_DESC* pDesc);
		ID3D11Texture2D* GetD3DTexture2D() const;

	private:
		void Init();
		void Create();
		void CreateTex2D(const DXGI_FORMAT& format);
		void CreateShaderResourceView(const DXGI_FORMAT& format);
		void CreateSamplerState(const DXGI_FORMAT& format);

	private:
		// 2次元テクスチャの設定
		D3D11_TEXTURE2D_DESC m_TextureDesc{};
	};
}