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
		// ���_�V�F�[�_�[�̓ǂݍ���
		static void VertexShaderLoad(GUID* guid, const std::string& fileName, const D3D11_INPUT_ELEMENT_DESC* layout, const UINT arraySize, const std::string& entryPoint = "vsMain");
		// �s�N�Z���V�F�[�_�[�̓ǂݍ���
		static void PixelShaderLoad(GUID* guid, const std::string& fileName, const std::string& entryPoint = "psMain");
		// �W�I���g���V�F�[�_�[�̓ǂݍ���
		static void GeometryShaderLoad(GUID* guid, const std::string& fileName, const std::string& entryPoint = "gsMain");
		// �R���s���[�g�V�F�[�_�[�̓ǂݍ���
		static void ComputeShaderLoad(GUID* guid, const std::string& fileName, const std::string& entryPoint = "csMain");
		// �n���V�F�[�_�[�̓ǂݍ���
		static void HullShaderLoad(GUID* guid, const std::string& fileName, const std::string& entryPoint = "hsMain");
		// �h���C���V�F�[�_�[�̓ǂݍ���
		static void DomainShaderLoad(GUID* guid, const std::string& fileName, const std::string& entryPoint = "dsMain");
	};
}