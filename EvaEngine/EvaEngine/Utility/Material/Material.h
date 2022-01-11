#pragma once

#include <GLTFSDK/GLTF.h>
#include "../ShaderUtility/Shader/Shader.h"
#include "../ModelUtility/ModelData/ShaderParameters.h"

namespace EvaEngine {
	struct Material {
		Material() = default;
		~Material() = default;

		DirectX::XMFLOAT4 ambient{ 1.0f, 1.0f, 1.0f, 1.0f };
		DirectX::XMFLOAT4 diffuse{ 1.0f, 1.0f, 1.0f, 1.0f };
		DirectX::XMFLOAT4 specular{ 1.0f, 1.0f, 1.0f, 1.0f };
		float alpha{ 0.0f };

	public:
		void Release();
		void SetShader(const Shader& shader);
		//void SetConstantBuffer(int size, )

	public:
		ID3D11ShaderResourceView* shaderResourcesView{ nullptr };

		Shader g_Shader{};
		ID3D11Texture2D* g_Texture{ nullptr };
		std::vector<char> g_ImageData;
		Microsoft::glTF::AlphaMode g_AlphaMode{};
	};
}