#pragma once

#include "../../../Utility/ModelUtility/ModelData/ModelData.h"

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
	int AddModelData(const ModelData::Model& model);
	// モデルデータを取得
	ModelData::Model GetModel(const int modelHandle);
	// モデルデータをメモリから消す
	void DeleteModel(const int modelHandle);
	// メモリにモデルのデータを読み込む
	ModelData::Model LoadModelDataMemory(const ModelData::Model& model);
	
private:
	// モデルデータのハンドル
	int modelCount{ 0 };
	// モデルデータ
	std::map<int, ModelData::Model> m_Model{};
};