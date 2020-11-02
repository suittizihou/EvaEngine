#pragma once
#include <string>
#include "../../../Define/D3D11Defines.h"

class ShaderCompiler {
public:
	// 頂点シェーダーのコンパイル
	static VertexShader CreateVertexShader(const std::string& fileName, const std::string& entrypath = "vsMain", bool error = true);
	// ピクセルシェーダーのコンパイル
	static PixelShader CreatePixelShader(const std::string& fileName, const std::string& entrypath = "psMain", bool error = true);
	// ジオメトリシェーダーのコンパイル
	static GeometryShader CreateGeometryShader(const std::string& fileName, const std::string& entrypath = "gsMain", bool error = true);
	// コンピュートシェーダーのコンパイル
	static ComputeShader CreateComputeShader(const std::string& fileName, const std::string& entrypath = "gsMain", bool error = true);
	// ハルシェーダーのコンパイル
	static HullShader CreateHullShader(const std::string& fileName, const std::string& entrypath = "hsMain", bool error = true);
	// ドメインシェーダーのコンパイル
	static DomainShader CreateDomainShader(const std::string& fileName, const std::string& entrypath = "dsMain", bool error = true);

	// セマンティクスのセットなどをするインプットレイアウトを作成
	static InputLayout CreateInputLayout(D3D11_INPUT_ELEMENT_DESC* layout, UINT elemNum, const std::string& fileName, const std::string& entryPath);

private:
	// シェーダーのエラーチェック
	static HRESULT ShaderErrorCheck(const std::string& fileName, const std::string& entryPath, const LPCSTR& pTarget, ID3DBlob** blob, bool error = true);
	// インプットレイアウトのエラーチェック
	static HRESULT InputLayoutErrorCheck(const std::string& fileName, const std::string& entryPath, const LPCSTR& pTarget, ID3DBlob** blob);
};