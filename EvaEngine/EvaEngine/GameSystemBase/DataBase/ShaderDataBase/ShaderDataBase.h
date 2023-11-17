#pragma once

#include "../../../Define/D3D11Defines.h"
#include "../../../Utility/ShaderUtility/ShaderBase/ShaderBase.h"
#include "../../../Utility/GUIDUtility/GUIDUtility.h"
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
			void AddVertexShader(const VertexShader& vertexShader, GUID* guid);
			// ピクセルシェーダーの追加
			void AddPixelShader(const PixelShader& pixelShader, GUID* guid);
			// ジオメトリシェーダーの追加
			void AddGeometryShader(const GeometryShader& geometryShader, GUID* guid);
			// コンピュートシェーダーの追加
			void AddComputeShader(const ComputeShader& computeShader, GUID* guid);
			// ハルシェーダーの追加
			void AddHullShader(const HullShader& hullShader, GUID* guid);
			// ドメインシェーダーの追加
			void AddDomainShader(const DomainShader& domainShader, GUID* guid);

			// デフォルトの頂点シェーダーを取得
			VertexShader GetDefaultVertexShader();
			// デフォルトのピクセルシェーダーを取得
			PixelShader GetDefaultPixelShader();

			// 頂点シェーダーの取得
			VertexShader GetVertexShader(const GUID& shaderHandle);
			// ピクセルシェーダーの取得
			PixelShader GetPixelShader(const GUID& shaderHandle);
			// ジオメトリシェーダーの取得
			GeometryShader GetGeometryShader(const GUID& shaderHandle);
			// コンピュートシェーダーの取得
			ComputeShader GetComputeShader(const GUID& shaderHandle);
			// ハルシェーダーの取得
			HullShader GetHullShader(const GUID& shaderHandle);
			// ドメインシェーダーの取得
			DomainShader GetDomainShader(const GUID& shaderHandle);

			// 頂点シェーダーの削除
			void DeleteVertexShader(const GUID& shaderHandle);
			// ピクセルシェーダーの削除
			void DeletePixelShader(const GUID& shaderHandle);
			// ジオメトリシェーダーの削除
			void DeleteGeometryShader(const GUID& shaderHandle);
			// コンピュートシェーダーの削除
			void DeleteComputeShader(const GUID& shaderHandle);
			// ハルシェーダーの削除
			void DeleteHullShader(const GUID& shaderHandle);
			// ドメインシェーダーの削除
			void DeleteDomainShader(const GUID& shaderHandle);

			// 全シェーダーリソースの解放
			void AllDeleteShader();

		private:
			bool GUIDCreate(GUID* guid, const std::string& shaderType);

		private:
			// コンパイル済み頂点シェーダー
			std::unordered_map<GUID, VertexShader> m_VertexShaders{};
			// コンパイル済みピクセルシェーダー
			std::unordered_map<GUID, PixelShader> m_PixelShaders{};
			// コンパイル済みジオメトリシェーダー
			std::unordered_map<GUID, GeometryShader> m_GeometryShaders{};
			// コンパイル済みコンピュートシェーダー
			std::unordered_map<GUID, ComputeShader> m_ComputeShaders{};
			// コンパイル済みハルシェーダー
			std::unordered_map<GUID, HullShader> m_HullShaders{};
			// コンパイル済みドメインシェーダー
			std::unordered_map<GUID, DomainShader> m_DomainShaders{};

			VertexShader m_DefaultVertexShader{};
			PixelShader m_DefaultPixelShader{};
		};
	}
}