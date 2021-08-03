#pragma once

#include "../../../Utility/ModelUtility/ModelData/ModelData.h"

namespace EvaEngine {
	namespace Internal {
		class ModelDataBase {
		private:
			ModelDataBase() = default;
			ModelDataBase(const ModelDataBase&);
			ModelDataBase operator=(const ModelDataBase&);
			~ModelDataBase();

		public:
			static ModelDataBase& Instance() {
				static ModelDataBase instance;
				return instance;
			}

			// ���f���f�[�^��ǉ�����
			int AddModelData(const EvaEngine::ModelData& model);
			// ���f���f�[�^���擾
			ModelData GetModel(const int modelHandle);
			// ���f���f�[�^���������������
			void DeleteModel(const int modelHandle);
			// �S���f���f�[�^���������������
			void AllDeleteModel();
			// �������Ƀ��f���̃f�[�^��ǂݍ���
			ModelData LoadModelDataMemory(const EvaEngine::ModelData& model);

		private:
			// ���f���f�[�^�̃n���h��
			int modelCount{ 0 };
			// ���f���f�[�^
			std::map<int, EvaEngine::ModelData> m_Models{};
		};
	}
}