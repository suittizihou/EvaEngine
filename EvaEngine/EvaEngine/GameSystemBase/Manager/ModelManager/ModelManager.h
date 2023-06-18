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

		// ���f���f�[�^�x�[�X���V�[���ɒǉ�
		void AddModelDataBase(const std::string& sceneName);

		// ���f����ǉ�
		void LoadModel(const std::string& fileName, GUID* guid);
		void LoadModel(const std::shared_ptr<ModelData>& model, GUID* guid);
		// ���f���f�[�^���擾
		std::weak_ptr<ModelData> GetModel(const GUID& guid);
		// ���f���f�[�^���폜
		void DeleteModel(const GUID& guid);
		void DeleteAllModel();

	private:
		std::unordered_map<std::string, std::shared_ptr<Internal::ModelDataBase>> m_ModelDatas;
	};
}