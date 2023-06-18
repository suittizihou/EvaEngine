#pragma once

#include "../../Define/D3D11Defines.h"
#include <vector>
#include <string>
#include <DirectXMath.h>
#include "../ModelUtility/ModelData/VertexData.h"

namespace EvaEngine {
	class Mesh {
	public:
		Mesh(int vertexSize = 0);
		~Mesh();

	public:
		// ���_�̐���ݒ�
		void SetVertexNum(int vertexSize);
		// ���_�̍\���̂�ݒ�
		void SetVertexData(std::vector<VertexData> vertexDatas, bool isCreateIndices = false);
		// �e���_�̍��W��ݒ�
		void SetVertexPos(int vertexNum, float x, float y, float z);
		// �e���_�̖@����ݒ�
		void SetVertexNormal(int vertexNum, float x, float y, float z);
		// �e���_�̐F��ݒ�
		void SetVertexColor(int vertexNum, float r, float g, float b, float a);
		// �e���_��UV���W��ݒ�
		void SetVertexUV(int vertexNum, float u, float v);
		// ���_�o�b�t�@�̐ݒ�
		void SetVertexBuffer(ID3D11Buffer* vertexBuffer);
		// ���_���g�p���鏇�Ԃ̍쐬(�C���f�b�N�X�o�b�t�@)
		std::vector<UINT> CreateIndices(const std::vector<VertexData>& vertexDatas);
		// ���_���g�p���鏇�Ԃ̐ݒ�(�C���f�b�N�X�o�b�t�@)
		void SetIndices(std::vector<unsigned int> indices);
		// �C���f�b�N�X�o�b�t�@�̐ݒ�
		void SetIndexBuffer(ID3D11Buffer* indexBuffer);
		// �}�e���A�����̐ݒ�
		void SetMaterialName(UINT materialID);
		void SetMaterialName(std::string materialName);

		// ���_���̎擾
		std::vector<VertexData> GetVertexData();
		// ���_�o�b�t�@�[�̎擾
		ID3D11Buffer* const* GetVertexBuffer();
		// ���_���g�p���鏇�Ԃ̎擾(�C���f�b�N�X�o�b�t�@)
		std::vector<unsigned int> GetIndices();
		// �C���f�b�N�X�o�b�t�@�̎擾
		ID3D11Buffer* GetIndexBuffer();
		// �}�e���A���̎擾
		std::string GetMaterialName() const;

		void Release();

	public:
		// ���b�V����
		std::string name{};

	private:
		// ���_�f�[�^�̔z��
		std::vector<VertexData> m_Vertexs;
		// �C���f�b�N�X�o�b�t�@
		std::vector<unsigned int> m_Indices;
		// �}�e���A��ID
		std::string m_MaterialName{};

		// GPU�p���_�o�b�t�@�[
		ID3D11Buffer* m_VertexBuffer{ nullptr };
		// GPU�p�C���f�b�N�X�o�b�t�@
		ID3D11Buffer* m_IndexBuffer{ nullptr };
	};
}