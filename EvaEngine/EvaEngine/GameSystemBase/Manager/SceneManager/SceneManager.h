#pragma once

#include "../../Base/Scene/Scene.h"
#include "../../DataBase/SceneDataBase/SceneDataBase.h"

namespace EvaEngine {
	class SceneManager {
	public:
		SceneManager() = default;
		~SceneManager() = default;

		typedef unsigned int UINT;

	public:
		// �V�[���̒ǉ�
		template<class T>
		static void AddScene(const std::string& sceneName) {
			EvaEngine::Internal::SceneDataBase::Instance().AddScene<T>(sceneName);
		}

		// �V�[���̃��[�h
		static void LoadScene(const std::string& sceneName);
		static void LoadScene(const UINT& sceneID);

		// ���݂̃V�[�������擾
		static std::string GetCurrentSceneName();
		// �O�̃V�[���������擾
		static std::string GetPreviousSceneName();
	};
}