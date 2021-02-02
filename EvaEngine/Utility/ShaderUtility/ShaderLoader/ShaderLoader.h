#pragma once

#include <string>
#include "../../../Define/D3D11Defines.h"

#ifdef EVAENGINE_EXPORTS
#define EVAENGINE_API __declspec(dllexport)
#else
#define EVAENGINE_API __declspec(dllimport)
#endif

class ShaderLoader {
private:
	ShaderLoader() = default;
	ShaderLoader(const ShaderLoader&);
	ShaderLoader operator=(const ShaderLoader&);
	~ShaderLoader() = default;

public:
	EVAENGINE_API static ShaderLoader& Instance() {
		static ShaderLoader instance;
		return instance;
	}

	// 頂点シェーダーの読み込み
	EVAENGINE_API int VertexShaderLoad(const std::string & fileName, const std::string& entryPoint = "vsMain");
	// ピクセルシェーダーの読み込み
	EVAENGINE_API int PixelShaderLoad(const std::string & fileName, const std::string& entryPoint = "psMain");
	// ジオメトリシェーダーの読み込み
	EVAENGINE_API int GeometryShaderLoad(const std::string & fileName, const std::string& entryPoint = "gsMain");
	// コンピュートシェーダーの読み込み
	EVAENGINE_API int ComputeShaderLoad(const std::string & fileName, const std::string& entryPoint = "csMain");
	// ハルシェーダーの読み込み
	EVAENGINE_API int HullShaderLoad(const std::string & fileName, const std::string& entryPoint = "hsMain");
	// ドメインシェーダーの読み込み
	EVAENGINE_API int DomainShaderLoad(const std::string & fileName, const std::string& entryPoint = "dsMain");
};