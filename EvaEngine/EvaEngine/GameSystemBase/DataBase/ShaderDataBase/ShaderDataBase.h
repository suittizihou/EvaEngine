#pragma once

#include "../../../Define/D3D11Defines.h"
#include "../../../Utility/ShaderUtility/ShaderBase/ShaderBase.h"
#include <unordered_map>

namespace EvaEngine {
	namespace Internal {
		class ShaderDataBase {
		private:
			ShaderDataBase() = default;
			ShaderDataBase(const ShaderDataBase&);
			ShaderDataBase operator=(const ShaderDataBase&);
			~ShaderDataBase();

		public:
			static ShaderDataBase& Instance() {
				static ShaderDataBase instance;
				return instance;
			}

			// デフォルトのシェーダー読み込み
			void LoadDefaultShader();

			// 頂点シェーダーの追加
			int AddVertexShader(const VertexShader& vertexShader);
			// ピクセルシェーダーの追加
			int AddPixelShader(const PixelShader& pixelShader);
			// ジオメトリシェーダーの追加
			int AddGeometryShader(const GeometryShader& geometryShader);
			// コンピュートシェーダーの追加
			int AddComputeShader(const ComputeShader& computeShader);
			// ハルシェーダーの追加
			int AddHullShader(const HullShader& hullShader);
			// ドメインシェーダーの追加
			int AddDomainShader(const DomainShader& domainShader);

			// デフォルトの頂点シェーダーを取得
			VertexShader GetDefaultVertexShader();
			// デフォルトのピクセルシェーダーを取得
			PixelShader GetDefaultPixelShader();

			// 頂点シェーダーの取得
			VertexShader GetVertexShader(const int shaderHandle);
			// ピクセルシェーダーの取得
			PixelShader GetPixelShader(const int shaderHandle);
			// ジオメトリシェーダーの取得
			GeometryShader GetGeometryShader(const int shaderHandle);
			// コンピュートシェーダーの取得
			ComputeShader GetComputeShader(const int shaderHandle);
			// ハルシェーダーの取得
			HullShader GetHullShader(const int shaderHandle);
			// ドメインシェーダーの取得
			DomainShader GetDomainShader(const int shaderHandle);

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
			void AllDeleteShader();


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
			std::unordered_map<int, VertexShader> m_VertexShaders{};
			// コンパイル済みピクセルシェーダー
			std::unordered_map<int, PixelShader> m_PixelShaders{};
			// コンパイル済みジオメトリシェーダー
			std::unordered_map<int, GeometryShader> m_GeometryShaders{};
			// コンパイル済みコンピュートシェーダー
			std::unordered_map<int, ComputeShader> m_ComputeShaders{};
			// コンパイル済みハルシェーダー
			std::unordered_map<int, HullShader> m_HullShaders{};
			// コンパイル済みドメインシェーダー
			std::unordered_map<int, DomainShader> m_DomainShaders{};

			VertexShader m_DefaultVertexShader{};
			PixelShader m_DefaultPixelShader{};
		};
	}
}