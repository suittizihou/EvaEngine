#pragma once

#include <string>
#include <d3d11.h>

#undef LoadImage

namespace EvaEngine {
	class TextureLoader {
	public:
		static bool LoadImage(const std::string& fileName, ID3D11Resource** texture, ID3D11ShaderResourceView** textureView);
	};
}