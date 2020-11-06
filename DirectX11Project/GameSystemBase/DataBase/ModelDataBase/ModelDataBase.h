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
	int AddModelData(const My3DLib::Model& model);
	// モデルデータを取得
	My3DLib::Model GetModel(const int modelHandle);
	// モデルデータをメモリから消す
	void DeleteModel(const int modelHandle);
	// メモリにモデルのデータを読み込む
	My3DLib::Model LoadModelDataMemory(const My3DLib::Model& model);
	
private:
	// モデルデータのハンドル
	int modelCount{ 0 };
	// モデルデータ
	std::map<int, My3DLib::Model> m_Models{};
};