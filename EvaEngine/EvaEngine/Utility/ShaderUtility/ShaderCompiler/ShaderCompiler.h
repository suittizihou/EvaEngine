#pragma once
#include <string>
#include "../../../Define/D3D11Defines.h"

namespace EvaEngine {
	namespace Internal {
		class ShaderCompiler {
		public:
			// 頂点シェーダーのコンパイル
			static ID3D11VertexShader* CreateVertexShader(const std::string& fileName, const std::string& entrypath = "vsMain", bool error = true);
			// ピクセルシェーダーのコンパイル
			static ID3D11PixelShader* CreatePixelShader(const std::string& fileName, const std::string& entrypath = "psMain", bool error = true);
			// ジオメトリシェーダーのコンパイル
			static ID3D11GeometryShader* CreateGeometryShader(const std::string& fileName, const std::string& entrypath = "gsMain", bool error = true);
			// コンピュートシェーダーのコンパイル
			static ID3D11ComputeShader* CreateComputeShader(const std::string& fileName, const std::string& entrypath = "gsMain", bool error = true);
			// ハルシェーダーのコンパイル
			static ID3D11HullShader* CreateHullShader(const std::string& fileName, const std::string& entrypath = "hsMain", bool error = true);
			// ドメインシェーダーのコンパイル
			static ID3D11DomainShader* CreateDomainShader(const std::string& fileName, const std::string& entrypath = "dsMain", bool error = true);

			// セマンティクスのセットなどをする頂点レイアウトを作成
			static ID3D11InputLayout* CreateVertexLayout(D3D11_INPUT_ELEMENT_DESC* layout, UINT elemNum, const std::string& fileName, const std::string& entryPath);

		private:
			// シェーダーのエラーチェック
			static HRESULT ShaderErrorCheck(const std::string& fileName, const std::string& entryPath, const LPCSTR& pTarget, ID3DBlob** blob, bool error = true);
			// インプットレイアウトのエラーチェック
			static HRESULT InputLayoutErrorCheck(const std::string& fileName, const std::string& entryPath, const LPCSTR& pTarget, ID3DBlob** blob);
		};
	}
}