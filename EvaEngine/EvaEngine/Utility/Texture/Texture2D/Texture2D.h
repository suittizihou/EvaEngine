#pragma once

#include "../Texture/Texture.h"

namespace EvaEngine {
	class Texture2D : public Texture {
	public:
		Texture2D();
		~Texture2D();

		void STDMETHODCALLTYPE GetD3DTexture2D(_Out_ D3D11_TEXTURE2D_DESC* pDesc);

	private:
		Internal::D3DTexture2D m_Texture2D{ nullptr };
	};
}