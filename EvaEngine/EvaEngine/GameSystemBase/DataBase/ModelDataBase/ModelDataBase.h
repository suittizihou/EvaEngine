#pragma once
#include <memory>
#include <unordered_map>
#include <guiddef.h>
#include "../../../Utility/GUIDUtility/GUIDUtility.h"
#include "../../../Utility/ModelUtility/ModelData/ModelData.h"

namespace EvaEngine {
	namespace Internal {
		class ModelDataBase {
		public:
			ModelDataBase() = default;
			~ModelDataBase() = default;

			// ���f���f�[�^��ǉ�����
			void LoadModelData(const std::shared_ptr<EvaEngine::ModelData>& model, GUID* guid);
			void LoadModelData(const std::string& fileName, GUID* guid);
			// ���f���f�[�^���擾
			std::weak_ptr<ModelData> GetModel(const GUID& guid);
			// ���f���f�[�^���������������
			void DeleteModel(const GUID& guid);
			// �S���f���f�[�^���������������
			void DeleteAllModel();
			//// �������Ƀ��f���̃f�[�^��ǂݍ���
			//ModelData LoadModelDataMemory(const std::shared_ptr<EvaEngine::ModelData>& model);

		private:
			// ���f���f�[�^
			std::unordered_map<GUID, std::shared_ptr<EvaEngine::ModelData>> m_Models{};
		};
	}
}