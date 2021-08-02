#pragma once

#include "../../Base/Scene/Scene.h"

#include <map>
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
				static_assert(std::is_base_of<Scene, T>::value == true, "The argument does not inherit from Scene.");

				// Editorという名前のシーン名は登録できない
				if (sceneName == "Editor") {
					DebugLog::LogError(u8"You cannot use the name ""Editor"" in the scene name.");
					return;
				}

				// 同じシーン名が既に登録されていれば返す
				if (m_Scenes.count(sceneName) >= 1) {
					DebugLog::LogError(u8"A scene with the same name has already been registered.");
					return;
				}

				std::shared_ptr<T> scene = std::make_shared<T>(sceneName, m_Scenes.size());
				m_Scenes[sceneName] = scene;
				ComponentManager::Instance().AddComponentDataBase(sceneName);
				GameObjectManager::Instance().AddGameObjectDataBase(sceneName);
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
			void SceneChange();

			// シーンのタスクシステムを回す
			void Initialize();
			void SceneUpdate();
			void FixedUpdate();
			void Update();
			void LateUpdate();
			void Draw(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& command);

#if _DEBUG
			void OnGUI();
#endif

		private:
			bool m_IsChangeScene{};
			std::string m_CurrentSceneName{};
			std::string m_PreviousSceneName{};
			std::weak_ptr<Scene> m_CurrentScene;
			std::map<std::string, std::shared_ptr<Scene>> m_Scenes;
		};
	}
}