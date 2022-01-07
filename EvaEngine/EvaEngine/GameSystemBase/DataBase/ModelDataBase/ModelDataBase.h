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

			// モデルデータを追加する
			int LoadModelData(const std::shared_ptr<EvaEngine::ModelData>& model);
			int LoadModelData(const std::string& fileName);
			// モデルデータを取得
			std::weak_ptr<ModelData> GetModel(const int modelHandle);
			// モデルデータをメモリから消す
			void DeleteModel(const int modelHandle);
			// 全モデルデータをメモリから消す
			void DeleteAllModel();
			//// メモリにモデルのデータを読み込む
			//ModelData LoadModelDataMemory(const std::shared_ptr<EvaEngine::ModelData>& model);

		private:
			// モデルデータのハンドル
			int modelCount{ 0 };
			// モデルデータ
			std::unordered_map<int, std::shared_ptr<EvaEngine::ModelData>> m_Models{};
		};
	}
}