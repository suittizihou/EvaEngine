#pragma once

#include <string>
#include "../../../Define/D3D11Defines.h"

class ShaderLoader {
private:
	ShaderLoader() = default;
	ShaderLoader(const ShaderLoader&);
	ShaderLoader operator=(const ShaderLoader&);
	~ShaderLoader() = default;

public:
	// 頂点シェーダーの読み込み
	static int VertexShaderLoad(const std::string & fileName, const std::string& entryPoint = "vsMain");
	// ピクセルシェーダーの読み込み
	static int PixelShaderLoad(const std::string & fileName, const std::string& entryPoint = "psMain");
	// ジオメトリシェーダーの読み込み
	static int GeometryShaderLoad(const std::string & fileName, const std::string& entryPoint = "gsMain");
	// コンピュートシェーダーの読み込み
	static int ComputeShaderLoad(const std::string & fileName, const std::string& entryPoint = "csMain");
	// ハルシェーダーの読み込み
	static int HullShaderLoad(const std::string & fileName, const std::string& entryPoint = "hsMain");
	// ドメインシェーダーの読み込み
	static int DomainShaderLoad(const std::string & fileName, const std::string& entryPoint = "dsMain");
};