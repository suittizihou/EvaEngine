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
		// シーンの追加
		template<class T>
		static void AddScene(const std::string& sceneName) {
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