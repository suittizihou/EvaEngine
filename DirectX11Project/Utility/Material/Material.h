#pragma once

#include "../ShaderUtility/Shader/Shader.h"

namespace My3DLib {
	class Material {
	public:
		Shader g_Shader{};
		Texture2D g_Texture{};

	private:
		InputLayout m_InputLayout{ nullptr };
		ConstantBuffer m_ConstantBuffer{ nullptr };
	};
}