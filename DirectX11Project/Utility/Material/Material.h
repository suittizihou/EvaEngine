#pragma once

#include "../Shader/Shader.h"

class Material {
public:
	Shader g_Shader{};
	Texture2D g_Texture{};

private:
	ConstantBuffer m_ConstantBuffer{ nullptr };
};