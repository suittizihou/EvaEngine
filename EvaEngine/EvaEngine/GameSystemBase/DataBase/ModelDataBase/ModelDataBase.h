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

			// モデルデータを追加する
			void LoadModelData(const std::shared_ptr<EvaEngine::ModelData>& model, GUID* guid);
			void LoadModelData(const std::string& fileName, GUID* guid);
			// モデルデータを取得
			std::weak_ptr<ModelData> GetModel(const GUID& guid);
			// モデルデータをメモリから消す
			void DeleteModel(const GUID& guid);
			// 全モデルデータをメモリから消す
			void DeleteAllModel();
			//// メモリにモデルのデータを読み込む
			//ModelData LoadModelDataMemory(const std::shared_ptr<EvaEngine::ModelData>& model);

		private:
			// モデルデータ
			std::unordered_map<GUID, std::shared_ptr<EvaEngine::ModelData>> m_Models{};
		};
	}
}