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

	protected:
		Vector2 texelSize{ Vector2::zero() };
		TextureType textureType{ TextureType::None };
	};
}