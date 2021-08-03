#pragma once
#include <string>
#include "../../../Define/D3D11Defines.h"

namespace EvaEngine {
	namespace Internal {
		class VertexShader;
		class PixelShader;
		class GeometryShader;
		class ComputeShader;
		class HullShader;
		class DomainShader;

		class ShaderCompiler {
			ShaderCompiler() = default;
			~ShaderCompiler() = default;

		public:
			// 頂点シェーダーを作成
			static HRESULT CreateVertexShader(VertexShader* shader, const D3D11_INPUT_ELEMENT_DESC* layout, const UINT arraySize, const std::string& fileName, const std::string& entrypath = "vsMain", bool error = true);
			// ピクセルシェーダーを作成
			static HRESULT CreatePixelShader(PixelShader* shader, const std::string& fileName, const std::string& entrypath = "psMain", bool error = true);
			// ジオメトリシェーダーを作成
			static HRESULT CreateGeometryShader(GeometryShader* shader, const std::string& fileName, const std::string& entrypath = "gsMain", bool error = true);
			// コンピュートシェーダーを作成
			static HRESULT CreateComputeShader(ComputeShader* shader, const std::string& fileName, const std::string& entrypath = "gsMain", bool error = true);
			// ハルシェーダーを作成
			static HRESULT CreateHullShader(HullShader* shader, const std::string& fileName, const std::string& entrypath = "hsMain", bool error = true);
			// ドメインシェーダーを作成
			static HRESULT CreateDomainShader(DomainShader* shader, const std::string& fileName, const std::string& entrypath = "dsMain", bool error = true);

		private:
			// セマンティクスのセットなどをする頂点レイアウトを作成
			static HRESULT CreateInputLayout(VertexShader* shader, const D3D11_INPUT_ELEMENT_DESC* layout, const UINT arraySize);
			// シェーダーのコンパイル
			static HRESULT Compile(const std::string& fileName, const std::string& entryPath, const LPCSTR& pTarget, ID3DBlob** blob, bool error = true);
		};
	}
}