#pragma once

#include "../Texture/Texture.h"

namespace EvaEngine {
	class Texture2D : public Texture {
	public:
		Texture2D(const UINT width, const UINT height);
		Texture2D(const UINT width, const UINT height, const DXGI_FORMAT& textureFormat);
		Texture2D(const UINT width, const UINT height, const D3D11_TEXTURE2D_DESC& textureDesc);
		~Texture2D();

		void STDMETHODCALLTYPE GetD3DTexture2D(_Out_ D3D11_TEXTURE2D_DESC* pDesc);

	private:
		void Init();
		void Create();
	private:
		// 2次元テクスチャの設定
		D3D11_TEXTURE2D_DESC m_TextureDesc{};
		Internal::D3DTexture2D m_Texture2D{ nullptr };
	};
}