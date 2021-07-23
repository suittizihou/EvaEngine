#pragma once

#include "../Texture/Texture.h"

namespace EvaEngine {
	class Texture2D;

	class RenderTexture : public Texture {
	public:
		RenderTexture();
	private:
		void Create();
	private:
		Texture2D* m_Texture2D{ nullptr };
	};
}