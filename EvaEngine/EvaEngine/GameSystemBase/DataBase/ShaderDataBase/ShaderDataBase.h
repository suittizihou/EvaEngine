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

			// �f�t�H���g�̃V�F�[�_�[�ǂݍ���
			void LoadDefaultShader();

			// ���_�V�F�[�_�[�̒ǉ�
			int AddVertexShader(const VertexShader& vertexShader);
			// �s�N�Z���V�F�[�_�[�̒ǉ�
			int AddPixelShader(const PixelShader& pixelShader);
			// �W�I���g���V�F�[�_�[�̒ǉ�
			int AddGeometryShader(const GeometryShader& geometryShader);
			// �R���s���[�g�V�F�[�_�[�̒ǉ�
			int AddComputeShader(const ComputeShader& computeShader);
			// �n���V�F�[�_�[�̒ǉ�
			int AddHullShader(const HullShader& hullShader);
			// �h���C���V�F�[�_�[�̒ǉ�
			int AddDomainShader(const DomainShader& domainShader);

			// �f�t�H���g�̒��_�V�F�[�_�[���擾
			VertexShader GetDefaultVertexShader();
			// �f�t�H���g�̃s�N�Z���V�F�[�_�[���擾
			PixelShader GetDefaultPixelShader();

			// ���_�V�F�[�_�[�̎擾
			VertexShader GetVertexShader(const int shaderHandle);
			// �s�N�Z���V�F�[�_�[�̎擾
			PixelShader GetPixelShader(const int shaderHandle);
			// �W�I���g���V�F�[�_�[�̎擾
			GeometryShader GetGeometryShader(const int shaderHandle);
			// �R���s���[�g�V�F�[�_�[�̎擾
			ComputeShader GetComputeShader(const int shaderHandle);
			// �n���V�F�[�_�[�̎擾
			HullShader GetHullShader(const int shaderHandle);
			// �h���C���V�F�[�_�[�̎擾
			DomainShader GetDomainShader(const int shaderHandle);

			// ���_�V�F�[�_�[�̍폜
			void DeleteVertexShader(const int shaderHandle);
			// �s�N�Z���V�F�[�_�[�̍폜
			void DeletePixelShader(const int shaderHandle);
			// �W�I���g���V�F�[�_�[�̍폜
			void DeleteGeometryShader(const int shaderHandle);
			// �R���s���[�g�V�F�[�_�[�̍폜
			void DeleteComputeShader(const int shaderHandle);
			// �n���V�F�[�_�[�̍폜
			void DeleteHullShader(const int shaderHandle);
			// �h���C���V�F�[�_�[�̍폜
			void DeleteDomainShader(const int shaderHandle);

			// �S�V�F�[�_�[���\�[�X�̉��
			void AllDeleteShader();


		private:
			// ���_�V�F�[�_�[�̃n���h��
			int m_VertexShaderCount{ 0 };
			// �s�N�Z���V�F�[�_�[�̃n���h��
			int m_PixelShaderCount{ 0 };
			// �W�I���g���V�F�[�_�[�̃n���h��
			int m_GeometryShaderCount{ 0 };
			// �R���s���[�g�V�F�[�_�[�̃n���h��
			int m_ComputeShaderCount{ 0 };
			// �n���V�F�[�_�[�̃n���h��
			int m_HullShaderCount{ 0 };
			// �h���C���V�F�[�_�[�̃n���h��
			int m_DomainShaderCount{ 0 };

			// �R���p�C���ςݒ��_�V�F�[�_�[
			std::unordered_map<int, VertexShader> m_VertexShaders{};
			// �R���p�C���ς݃s�N�Z���V�F�[�_�[
			std::unordered_map<int, PixelShader> m_PixelShaders{};
			// �R���p�C���ς݃W�I���g���V�F�[�_�[
			std::unordered_map<int, GeometryShader> m_GeometryShaders{};
			// �R���p�C���ς݃R���s���[�g�V�F�[�_�[
			std::unordered_map<int, ComputeShader> m_ComputeShaders{};
			// �R���p�C���ς݃n���V�F�[�_�[
			std::unordered_map<int, HullShader> m_HullShaders{};
			// �R���p�C���ς݃h���C���V�F�[�_�[
			std::unordered_map<int, DomainShader> m_DomainShaders{};

			VertexShader m_DefaultVertexShader{};
			PixelShader m_DefaultPixelShader{};
		};
	}
}