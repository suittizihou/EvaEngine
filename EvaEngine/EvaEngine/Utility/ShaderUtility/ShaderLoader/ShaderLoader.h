#pragma once

#include <string>
#include "../../../Define/D3D11Defines.h"
#include "../../../Utility/GUIDUtility/GUIDUtility.h"

namespace EvaEngine {
	class ShaderLoader {
	private:
		ShaderLoader() = default;
		ShaderLoader(const ShaderLoader&);
		ShaderLoader operator=(const ShaderLoader&);
		~ShaderLoader() = default;

	public:
		// 頂点シェーダーの読み込み
		static void VertexShaderLoad(GUID* guid, const std::string& fileName, const D3D11_INPUT_ELEMENT_DESC* layout, const UINT arraySize, const std::string& entryPoint = "vsMain");
		// ピクセルシェーダーの読み込み
		static void PixelShaderLoad(GUID* guid, const std::string& fileName, const std::string& entryPoint = "psMain");
		// ジオメトリシェーダーの読み込み
		static void GeometryShaderLoad(GUID* guid, const std::string& fileName, const std::string& entryPoint = "gsMain");
		// コンピュートシェーダーの読み込み
		static void ComputeShaderLoad(GUID* guid, const std::string& fileName, const std::string& entryPoint = "csMain");
		// ハルシェーダーの読み込み
		static void HullShaderLoad(GUID* guid, const std::string& fileName, const std::string& entryPoint = "hsMain");
		// ドメインシェーダーの読み込み
		static void DomainShaderLoad(GUID* guid, const std::string& fileName, const std::string& entryPoint = "dsMain");
	};
}