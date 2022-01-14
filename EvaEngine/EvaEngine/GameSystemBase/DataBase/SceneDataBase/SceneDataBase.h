#pragma once

#include "../../Base/Scene/Scene.h"

#include <unordered_map>
#include <string>
#include <memory>

namespace EvaEngine {
	namespace Internal {
		class SceneDataBase {
		private:
			SceneDataBase() = default;
			SceneDataBase(const SceneDataBase&);
			SceneDataBase& operator=(const SceneDataBase&);
			~SceneDataBase() = default;

		public:
			static SceneDataBase& Instance() {
				static SceneDataBase instance;
				return instance;
			}

			// シーンの追加
			template<class T>
			void AddScene(const std::string& sceneName) {
				// Editorという名前のシーン名は登録できない
				if (sceneName == "Editor") {
					DebugLog::LogError("You cannot use the name ""Editor"" in the scene name.");
					return;
				}

				// 同じシーン名が既に登録されていれば返す
				if (m_Scenes.count(sceneName) >= 1) {
					DebugLog::LogError("A scene with the same name has already been registered.");
					return;
				}

				std::shared_ptr<T> scene = std::make_shared<T>(sceneName, m_Scenes.size());
				m_Scenes[sceneName] = scene;
				ComponentManager::Instance().AddComponentDataBase(sceneName);
				GameObjectManager::Instance().AddGameObjectDataBase(sceneName);
				ModelManager::Instance().AddModelDataBase(sceneName);
			}

			// シーンのロード
			void LoadScene(const std::string& sceneName);
			void LoadScene(const UINT& sceneID);
			// 今のシーン名を返す
			std::string GetCurrentSceneName() const;
			// 前のシーン名を返す
			std::string GetPreviousSceneName() const;
			// シーンの初期化を行う
			HRESULT InitializeScene();
			// シーンを変える
			HRESULT SceneChange();
			// シーンが存在するかチェック
			bool IsCheckExists(const std::string& sceneName);
			// 登録されているシーンの数を返す
			size_t GetSceneCount() const;

			// シーンのタスクシステムを回す
			void Initialize();
			void SceneUpdate();
			void FixedUpdate();
			void Update();
			void ExecuteEditUpdate();
			void LateUpdate();
			void Draw(ID3D11DeviceContext* command);

#if _DEBUG
			void OnGUI();
#endif

		public:
			void AllDeleteScene();

		private:
			bool m_IsChangeScene{};
			std::string m_CurrentSceneName{};
			std::string m_PreviousSceneName{};
			std::weak_ptr<Scene> m_CurrentScene;
			std::unordered_map<std::string, std::shared_ptr<Scene>> m_Scenes;
		};
	}
}