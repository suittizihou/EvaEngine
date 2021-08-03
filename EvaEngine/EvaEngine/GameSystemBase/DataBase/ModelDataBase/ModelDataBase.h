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

			// モデルデータを追加する
			int AddModelData(const EvaEngine::ModelData& model);
			// モデルデータを取得
			ModelData GetModel(const int modelHandle);
			// モデルデータをメモリから消す
			void DeleteModel(const int modelHandle);
			// 全モデルデータをメモリから消す
			void AllDeleteModel();
			// メモリにモデルのデータを読み込む
			ModelData LoadModelDataMemory(const EvaEngine::ModelData& model);

		private:
			// モデルデータのハンドル
			int modelCount{ 0 };
			// モデルデータ
			std::map<int, EvaEngine::ModelData> m_Models{};
		};
	}
}