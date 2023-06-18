#pragma once

#include "../../Base/Scene/Scene.h"
#include "../../DataBase/SceneDataBase/SceneDataBase.h"

namespace EvaEngine {
	class SceneManager {
		SceneManager() = default;
		~SceneManager() = default;
	public:

		typedef unsigned int UINT;

	public:
		// �V�[���̒ǉ�
		template<class T>
		static void AddScene(const std::string& sceneName) {
			static_assert(std::is_base_of<Scene, T>::value == true, "The argument does not inherit from Scene.");
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