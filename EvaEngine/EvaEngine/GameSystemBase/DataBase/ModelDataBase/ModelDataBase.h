#pragma once

#include "../../../Utility/ModelUtility/ModelData/ModelData.h"

namespace EvaEngine {
	namespace Internal {
		class ModelDataBase {
		private:
			ModelDataBase() = default;
			ModelDataBase(const ModelDataBase&);
			ModelDataBase operator=(const ModelDataBase&);
			~ModelDataBase() = default;

		public:
			static ModelDataBase& Instance() {
				static ModelDataBase instance;
				return instance;
			}

			// ���f���f�[�^��ǉ�����
			int AddModelData(const ModelData& model);
			// ���f���f�[�^���擾
			ModelData GetModel(const int modelHandle);
			// ���f���f�[�^���������������
			void DeleteModel(const int modelHandle);
			// �������Ƀ��f���̃f�[�^��ǂݍ���
			ModelData LoadModelDataMemory(const ModelData& model);

		private:
			// ���f���f�[�^�̃n���h��
			int modelCount{ 0 };
			// ���f���f�[�^
			std::map<int, ModelData> m_Models{};
		};
	}
}