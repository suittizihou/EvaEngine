#pragma once
#include <string>
#include <memory>
#include <map>

namespace EvaEngine {
	class ModelData;

	namespace Internal {
		class ModelDataBase;
	}

	class ModelManager {
	private:
		ModelManager() = default;
		~ModelManager() = default;

		ModelManager(const ModelManager&);
		ModelManager& operator=(const ModelManager&);

	public:
		static ModelManager& Instance() {
			static ModelManager modelManager;
			return modelManager;
		}

		// モデルデータベースをシーンに追加
		void AddModelDataBase(const std::string& sceneName);

		// モデルを追加
		int LoadModel(const std::string& fileName);
		int LoadModel(const std::shared_ptr<ModelData>& model);
		// モデルデータを取得
		std::weak_ptr<ModelData> GetModel(const int modelHandle);
		// モデルデータを削除
		void DeleteModel(const int modelHandle);
		void DeleteAllModel();

	private:
		std::map <std::string, std::shared_ptr<Internal::ModelDataBase>> m_ModelDatas;
	};
}