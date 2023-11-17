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
		// シーンの追加
		template<class T>
		static void AddScene(const std::string& sceneName) {
			static_assert(std::is_base_of<Scene, T>::value == true, "The argument does not inherit from Scene.");
			EvaEngine::Internal::SceneDataBase::Instance().AddScene<T>(sceneName);
		}

		// シーンのロード
		static void LoadScene(const std::string& sceneName);
		static void LoadScene(const UINT& sceneID);

		// 現在のシーン名を取得
		static std::string GetCurrentSceneName();
		// 前のシーン名をを取得
		static std::string GetPreviousSceneName();
	};
}