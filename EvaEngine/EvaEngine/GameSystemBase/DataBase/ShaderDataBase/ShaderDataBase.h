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

			// �f�t�H���g�̃V�F�[�_�[�ǂݍ���
			void LoadDefaultShader();

			// ���_�V�F�[�_�[�̒ǉ�
			void AddVertexShader(const VertexShader& vertexShader, GUID* guid);
			// �s�N�Z���V�F�[�_�[�̒ǉ�
			void AddPixelShader(const PixelShader& pixelShader, GUID* guid);
			// �W�I���g���V�F�[�_�[�̒ǉ�
			void AddGeometryShader(const GeometryShader& geometryShader, GUID* guid);
			// �R���s���[�g�V�F�[�_�[�̒ǉ�
			void AddComputeShader(const ComputeShader& computeShader, GUID* guid);
			// �n���V�F�[�_�[�̒ǉ�
			void AddHullShader(const HullShader& hullShader, GUID* guid);
			// �h���C���V�F�[�_�[�̒ǉ�
			void AddDomainShader(const DomainShader& domainShader, GUID* guid);

			// �f�t�H���g�̒��_�V�F�[�_�[���擾
			VertexShader GetDefaultVertexShader();
			// �f�t�H���g�̃s�N�Z���V�F�[�_�[���擾
			PixelShader GetDefaultPixelShader();

			// ���_�V�F�[�_�[�̎擾
			VertexShader GetVertexShader(const GUID& shaderHandle);
			// �s�N�Z���V�F�[�_�[�̎擾
			PixelShader GetPixelShader(const GUID& shaderHandle);
			// �W�I���g���V�F�[�_�[�̎擾
			GeometryShader GetGeometryShader(const GUID& shaderHandle);
			// �R���s���[�g�V�F�[�_�[�̎擾
			ComputeShader GetComputeShader(const GUID& shaderHandle);
			// �n���V�F�[�_�[�̎擾
			HullShader GetHullShader(const GUID& shaderHandle);
			// �h���C���V�F�[�_�[�̎擾
			DomainShader GetDomainShader(const GUID& shaderHandle);

			// ���_�V�F�[�_�[�̍폜
			void DeleteVertexShader(const GUID& shaderHandle);
			// �s�N�Z���V�F�[�_�[�̍폜
			void DeletePixelShader(const GUID& shaderHandle);
			// �W�I���g���V�F�[�_�[�̍폜
			void DeleteGeometryShader(const GUID& shaderHandle);
			// �R���s���[�g�V�F�[�_�[�̍폜
			void DeleteComputeShader(const GUID& shaderHandle);
			// �n���V�F�[�_�[�̍폜
			void DeleteHullShader(const GUID& shaderHandle);
			// �h���C���V�F�[�_�[�̍폜
			void DeleteDomainShader(const GUID& shaderHandle);

			// �S�V�F�[�_�[���\�[�X�̉��
			void AllDeleteShader();

		private:
			bool GUIDCreate(GUID* guid, const std::string& shaderType);

		private:
			// �R���p�C���ςݒ��_�V�F�[�_�[
			std::unordered_map<GUID, VertexShader> m_VertexShaders{};
			// �R���p�C���ς݃s�N�Z���V�F�[�_�[
			std::unordered_map<GUID, PixelShader> m_PixelShaders{};
			// �R���p�C���ς݃W�I���g���V�F�[�_�[
			std::unordered_map<GUID, GeometryShader> m_GeometryShaders{};
			// �R���p�C���ς݃R���s���[�g�V�F�[�_�[
			std::unordered_map<GUID, ComputeShader> m_ComputeShaders{};
			// �R���p�C���ς݃n���V�F�[�_�[
			std::unordered_map<GUID, HullShader> m_HullShaders{};
			// �R���p�C���ς݃h���C���V�F�[�_�[
			std::unordered_map<GUID, DomainShader> m_DomainShaders{};

			VertexShader m_DefaultVertexShader{};
			PixelShader m_DefaultPixelShader{};
		};
	}
}