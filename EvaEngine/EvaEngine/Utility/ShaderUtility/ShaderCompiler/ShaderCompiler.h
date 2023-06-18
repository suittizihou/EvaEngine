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
			// ���_�V�F�[�_�[���쐬
			static HRESULT CreateVertexShader(VertexShader* shader, const D3D11_INPUT_ELEMENT_DESC* layout, const UINT arraySize, const std::string& fileName, const std::string& entrypath = "vsMain", bool error = true);
			// �s�N�Z���V�F�[�_�[���쐬
			static HRESULT CreatePixelShader(PixelShader* shader, const std::string& fileName, const std::string& entrypath = "psMain", bool error = true);
			// �W�I���g���V�F�[�_�[���쐬
			static HRESULT CreateGeometryShader(GeometryShader* shader, const std::string& fileName, const std::string& entrypath = "gsMain", bool error = true);
			// �R���s���[�g�V�F�[�_�[���쐬
			static HRESULT CreateComputeShader(ComputeShader* shader, const std::string& fileName, const std::string& entrypath = "gsMain", bool error = true);
			// �n���V�F�[�_�[���쐬
			static HRESULT CreateHullShader(HullShader* shader, const std::string& fileName, const std::string& entrypath = "hsMain", bool error = true);
			// �h���C���V�F�[�_�[���쐬
			static HRESULT CreateDomainShader(DomainShader* shader, const std::string& fileName, const std::string& entrypath = "dsMain", bool error = true);

		private:
			// �Z�}���e�B�N�X�̃Z�b�g�Ȃǂ����钸�_���C�A�E�g���쐬
			static HRESULT CreateInputLayout(VertexShader* shader, const D3D11_INPUT_ELEMENT_DESC* layout, const UINT arraySize);
			// �V�F�[�_�[�̃R���p�C��
			static HRESULT Compile(const std::string& fileName, const std::string& entryPath, const LPCSTR& pTarget, ID3DBlob** blob, bool error = true);
		};
	}
}