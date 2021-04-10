#pragma once

#include <GLTFSDK/GLTF.h>
#include "../ShaderUtility/Shader/Shader.h"
#include "../ModelUtility/ModelData/ShaderParameters.h"

namespace EvaEngine {
	struct Material {
		DirectX::XMFLOAT4 ambient{ 1.0f, 1.0f, 1.0f, 1.0f };
		DirectX::XMFLOAT4 diffuse{ 1.0f, 1.0f, 1.0f, 1.0f };
		DirectX::XMFLOAT4 specular{ 1.0f, 1.0f, 1.0f, 1.0f };
		float alpha{ 0.0f };

		ID3D11ShaderResourceView* shaderResourcesView{ nullptr };

		Shader g_Shader{};
		Texture2D g_Texture{};
		std::vector<char> g_ImageData;
		Microsoft::glTF::AlphaMode g_AlphaMode{};

	private:
		InputLayout m_InputLayout{ nullptr };
	};
}