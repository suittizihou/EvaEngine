#pragma once

#include <string>
#include "../../../Define/D3D11Defines.h"

namespace EvaEngine {
	class ShaderLoader {
	private:
		ShaderLoader() = default;
		ShaderLoader(const ShaderLoader&);
		ShaderLoader operator=(const ShaderLoader&);
		~ShaderLoader() = default;

	public:
		// ���_�V�F�[�_�[�̓ǂݍ���
		static int VertexShaderLoad(const std::string& fileName, const D3D11_INPUT_ELEMENT_DESC* layout, const UINT arraySize, const std::string& entryPoint = "vsMain");
		// �s�N�Z���V�F�[�_�[�̓ǂݍ���
		static int PixelShaderLoad(const std::string& fileName, const std::string& entryPoint = "psMain");
		// �W�I���g���V�F�[�_�[�̓ǂݍ���
		static int GeometryShaderLoad(const std::string& fileName, const std::string& entryPoint = "gsMain");
		// �R���s���[�g�V�F�[�_�[�̓ǂݍ���
		static int ComputeShaderLoad(const std::string& fileName, const std::string& entryPoint = "csMain");
		// �n���V�F�[�_�[�̓ǂݍ���
		static int HullShaderLoad(const std::string& fileName, const std::string& entryPoint = "hsMain");
		// �h���C���V�F�[�_�[�̓ǂݍ���
		static int DomainShaderLoad(const std::string& fileName, const std::string& entryPoint = "dsMain");
	};
}