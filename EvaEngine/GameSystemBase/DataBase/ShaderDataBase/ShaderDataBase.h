#pragma once

#include "../../../Define/D3D11Defines.h"
#include <map>

class ShaderDataBase {
private:
	ShaderDataBase() = default;
	ShaderDataBase(const ShaderDataBase&);
	ShaderDataBase operator=(const ShaderDataBase&);
	~ShaderDataBase() { DeleteAllShader(); };

public:
	static ShaderDataBase& Instance() {
		static ShaderDataBase instance;
		return instance;
	}

	// 頂点シェーダーの追加
	int AddVertexShader(ID3D11VertexShader* vertexShader);
	// ピクセルシェーダーの追加
	int AddPixelShader(ID3D11PixelShader* pixelShader);
	// ジオメトリシェーダーの追加
	int AddGeometryShader(ID3D11GeometryShader* geometryShader);
	// コンピュートシェーダーの追加
	int AddComputeShader(ID3D11ComputeShader* computeShader);
	// ハルシェーダーの追加
	int AddHullShader(ID3D11HullShader* hullShader);
	// ドメインシェーダーの追加
	int AddDomainShader(ID3D11DomainShader* domainShader);

	// 頂点シェーダーの取得
	ID3D11VertexShader* GetVertexShader(const int shaderHandle);
	// ピクセルシェーダーの取得
	ID3D11PixelShader* GetPixelShader(const int shaderHandle);
	// ジオメトリシェーダーの取得
	ID3D11GeometryShader* GetGeometryShader(const int shaderHandle);
	// コンピュートシェーダーの取得
	ID3D11ComputeShader* GetComputeShader(const int shaderHandle);
	// ハルシェーダーの取得
	ID3D11HullShader* GetHullShader(const int shaderHandle);
	// ドメインシェーダーの取得
	ID3D11DomainShader* GetDomainShader(const int shaderHandle);


	// 頂点シェーダーの削除
	void DeleteVertexShader(const int shaderHandle);
	// ピクセルシェーダーの削除
	void DeletePixelShader(const int shaderHandle);
	// ジオメトリシェーダーの削除
	void DeleteGeometryShader(const int shaderHandle);
	// コンピュートシェーダーの削除
	void DeleteComputeShader(const int shaderHandle);
	// ハルシェーダーの削除
	void DeleteHullShader(const int shaderHandle);
	// ドメインシェーダーの削除
	void DeleteDomainShader(const int shaderHandle);

	// 全シェーダーリソースの解放
	void DeleteAllShader();

private:
	// 頂点シェーダーのハンドル
	int m_VertexShaderCount{ 0 };
	// ピクセルシェーダーのハンドル
	int m_PixelShaderCount{ 0 };
	// ジオメトリシェーダーのハンドル
	int m_GeometryShaderCount{ 0 };
	// コンピュートシェーダーのハンドル
	int m_ComputeShaderCount{ 0 };
	// ハルシェーダーのハンドル
	int m_HullShaderCount{ 0 };
	// ドメインシェーダーのハンドル
	int m_DomainShaderCount{ 0 };
	
	// コンパイル済み頂点シェーダー
	std::map<int, ID3D11VertexShader*> m_VertexShaders{};
	// コンパイル済みピクセルシェーダー
	std::map<int, ID3D11PixelShader*> m_PixelShaders{};
	// コンパイル済みジオメトリシェーダー
	std::map<int, ID3D11GeometryShader*> m_GeometryShaders{};
	// コンパイル済みコンピュートシェーダー
	std::map<int, ID3D11ComputeShader*> m_ComputeShaders{};
	// コンパイル済みハルシェーダー
	std::map<int, ID3D11HullShader*> m_HullShaders{};
	// コンパイル済みドメインシェーダー
	std::map<int, ID3D11DomainShader*> m_DomainShaders{};
};