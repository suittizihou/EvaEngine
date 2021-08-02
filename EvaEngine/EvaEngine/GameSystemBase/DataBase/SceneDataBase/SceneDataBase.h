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

			// �V�[���̒ǉ�
			template<class T>
			void AddScene(const std::string& sceneName) {
				static_assert(std::is_base_of<Scene, T>::value == true, "The argument does not inherit from Scene.");

				// Editor�Ƃ������O�̃V�[�����͓o�^�ł��Ȃ�
				if (sceneName == "Editor") {
					DebugLog::LogError(u8"You cannot use the name ""Editor"" in the scene name.");
					return;
				}

				// �����V�[���������ɓo�^����Ă���ΕԂ�
				if (m_Scenes.count(sceneName) >= 1) {
					DebugLog::LogError(u8"A scene with the same name has already been registered.");
					return;
				}

				std::shared_ptr<T> scene = std::make_shared<T>(sceneName, m_Scenes.size());
				m_Scenes[sceneName] = scene;
				ComponentManager::Instance().AddComponentDataBase(sceneName);
				GameObjectManager::Instance().AddGameObjectDataBase(sceneName);
			}

			// �V�[���̃��[�h
			void LoadScene(const std::string& sceneName);
			void LoadScene(const UINT& sceneID);
			// ���̃V�[������Ԃ�
			std::string GetCurrentSceneName() const;
			// �O�̃V�[������Ԃ�
			std::string GetPreviousSceneName() const;
			// �V�[���̏��������s��
			HRESULT InitializeScene();
			// �V�[����ς���
			void SceneChange();

			// �V�[���̃^�X�N�V�X�e������
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