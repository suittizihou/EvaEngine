#pragma once
#include <d3d11.h>
#pragma comment(lib,"d3d11.lib")

#include <string>
#include <Windows.h>
#include <locale>

#include "../../../System/DebugLog/DebugLog.h"

namespace EvaEngine {
	namespace Internal {

		class InputLayout {
		public:
			InputLayout() = default;
			~InputLayout() = default;

			ID3D11InputLayout* m_pInputLayout{ nullptr };
		};

		template<class T>
		class ShaderBase
		{
		public:
			ShaderBase() : m_pShader(nullptr), m_pShaderCode(nullptr) {};
			virtual ~ShaderBase() = default;
			T* m_pShader{ nullptr };
			ID3DBlob* m_pShaderCode{ nullptr };
		};

		// 頂点シェーダー
		class VertexShader : public Internal::ShaderBase<ID3D11VertexShader> {
		public:
			VertexShader() = default;
			~VertexShader() = default;
			ID3D11InputLayout* m_pInputLayout{ nullptr };
		};

		// ピクセルシェーダー
		class PixelShader : public Internal::ShaderBase<ID3D11PixelShader> {
		public:
			PixelShader() = default;
			~PixelShader() = default;
		};

		// ジオメトリシェーダー
		class GeometryShader : public Internal::ShaderBase<ID3D11GeometryShader> {
		public:
			GeometryShader() = default;
			~GeometryShader() = default;
		};

		// コンピュートシェーダー
		class ComputeShader : public Internal::ShaderBase<ID3D11ComputeShader> {
		public:
			ComputeShader() = default;
			~ComputeShader() = default;
		};

		// ハルシェーダー
		class HullShader : public Internal::ShaderBase<ID3D11HullShader> {
		public:
			HullShader() = default;
			~HullShader() = default;
		};


		// ドメインシェーダー
		class DomainShader : public Internal::ShaderBase<ID3D11DomainShader> {
		public:
			DomainShader() = default;
			~DomainShader() = default;
		};
	}
}