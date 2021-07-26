#pragma once

#include <memory>
#include "../Texture/Texture.h"

namespace EvaEngine {
	class Texture2D;

	class RenderTexture : public Texture {
	public:
		RenderTexture(const UINT width, const UINT height);
	private:
		void Create();
	private:
		std::unique_ptr<Texture2D> m_pTexture2D{ nullptr };
	};
}