#pragma once
#include "../ShaderCompiler/ShaderCompiler.h"
#include "../ShaderBase/ShaderBase.h"

namespace EvaEngine {
	class Shader {
	public:
		Shader() = default;
		~Shader();

		// ���_�V�F�[�_�[���Z�b�g
		void SetVertexShader(const GUID& shaderHandle);
		void SetVertexShader(const Internal::VertexShader& shader);
		// �s�N�Z���V�F�[�_�[���Z�b�g
		void SetPixelShader(const GUID& shaderHandle);
		void SetPixelShader(const Internal::PixelShader& shader);
		// �W�I���g���V�F�[�_�[���Z�b�g
		void SetGeometryShader(const GUID& shaderHandle);
		void SetGeometryShader(const Internal::GeometryShader& shader);
		// �R���s���[�g�V�F�[�_�[���Z�b�g
		void SetComputeShader(const GUID& shaderHandle);
		void SetComputeShader(const Internal::ComputeShader& shader);
		// �n���V�F�[�_�[���Z�b�g
		void SetHullShader(const GUID& shaderHandle);
		void SetHullShader(const Internal::HullShader& shader);
		// �h���C���V�F�[�_�[���Z�b�g
		void SetDomainShader(const GUID& shaderHandle);
		void SetDomainShader(const Internal::DomainShader& shader);

		// ���_�V�F�[�_�[�̎擾
		Internal::VertexShader GetVertexShader();
		// �s�N�Z���V�F�[�_�[�̎擾
		Internal::PixelShader GetPixelShader();
		// �W�I���g���V�F�[�_�[�̎擾
		Internal::GeometryShader GetGeometryShader();
		// �R���s���[�g�V�F�[�_�[�̎擾
		Internal::ComputeShader GetComputeShader();
		// �n���V�F�[�_�[�̎擾
		Internal::HullShader GetHullShader();
		// �h���C���V�F�[�_�[�̎擾
		Internal::DomainShader GetDomainShader();

	private:
		//void AllRelease();

	private:
		Internal::VertexShader m_VertexShader{};
		Internal::PixelShader m_PixelShader{};
		Internal::GeometryShader m_GeometryShader{};
		Internal::ComputeShader m_ComputeShader{};
		Internal::HullShader m_HullShader{};
		Internal::DomainShader m_DomainShader{};
	};
}