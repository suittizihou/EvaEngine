#pragma once

#include "../../../Utility/ModelUtility/ModelData/ModelData.h"

namespace EvaEngine {

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

		// モデルデータを追加する
		int AddModelData(const ModelData& model);
		// モデルデータを取得
		ModelData GetModel(const int modelHandle);
		// モデルデータをメモリから消す
		void DeleteModel(const int modelHandle);
		// メモリにモデルのデータを読み込む
		ModelData LoadModelDataMemory(const ModelData& model);

	private:
		// モデルデータのハンドル
		int modelCount{ 0 };
		// モデルデータ
		std::map<int, ModelData> m_Models{};
	};
}