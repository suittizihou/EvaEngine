#pragma once
#include "../../../Define/D3D11Defines.h"
#include "../../Math/Vector2/Vector2.h"

namespace EvaEngine {
	class Texture {
	public:
		enum class TextureType {
			None,
			Tex2D,
			Tex3D
		};

	public:
		Texture() = default;
		virtual ~Texture() = default;

		TextureType GetTextureType() const;
		// Texture‚ÌƒTƒCƒY‚ðŽæ“¾
		Vector2 GetTexelSize() const;

	protected:
		Vector2 texelSize{ Vector2::zero() };
		TextureType textureType{ TextureType::None };
	};
}