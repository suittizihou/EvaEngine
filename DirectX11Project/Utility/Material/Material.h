#pragma once

#include <GLTFSDK/GLTF.h>
#include "../ShaderUtility/Shader/Shader.h"
#include "../ModelUtility/ModelData/ShaderParameters.h"

namespace My3DLib {
	class Material {
	public:
		Shader g_Shader{};
		Texture2D g_Texture{};
		std::vector<char> g_ImageData;
		Microsoft::glTF::AlphaMode g_AlphaMode{};

	private:
		InputLayout m_InputLayout{ nullptr };
	};
}