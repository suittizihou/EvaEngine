#pragma once
#include <memory>
#include <unordered_map>
#include "../../../Utility/ModelUtility/ModelData/ModelData.h"

namespace EvaEngine {
	namespace Internal {
		class ModelDataBase {
		public:
			ModelDataBase() = default;
			~ModelDataBase() = default;

			// ���f���f�[�^��ǉ�����
			int LoadModelData(const std::shared_ptr<EvaEngine::ModelData>& model);
			int LoadModelData(const std::string& fileName);
			// ���f���f�[�^���擾
			std::weak_ptr<ModelData> GetModel(const int modelHandle);
			// ���f���f�[�^���������������
			void DeleteModel(const int modelHandle);
			// �S���f���f�[�^���������������
			void DeleteAllModel();
			//// �������Ƀ��f���̃f�[�^��ǂݍ���
			//ModelData LoadModelDataMemory(const std::shared_ptr<EvaEngine::ModelData>& model);

		private:
			// ���f���f�[�^�̃n���h��
			int modelCount{ 0 };
			// ���f���f�[�^
			std::unordered_map<int, std::shared_ptr<EvaEngine::ModelData>> m_Models{};
		};
	}
}