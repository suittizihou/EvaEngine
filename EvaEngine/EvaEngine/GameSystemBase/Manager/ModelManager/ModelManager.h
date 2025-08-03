#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include <guiddef.h>

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
		void AddModelDataBase(const std::u8string& sceneName);

		// モデルを追加
		void LoadModel(const std::u8string& fileName, GUID* guid);
		void LoadModel(const std::shared_ptr<ModelData>& model, GUID* guid);
		// モデルデータを取得
		std::weak_ptr<ModelData> GetModel(const GUID& guid);
		// モデルデータを削除
		void DeleteModel(const GUID& guid);
		void DeleteAllModel();

	private:
		std::unordered_map<std::u8string, std::shared_ptr<Internal::ModelDataBase>> m_ModelDatas;
	};
}