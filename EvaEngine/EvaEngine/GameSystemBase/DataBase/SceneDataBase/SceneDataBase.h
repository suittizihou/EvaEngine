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

			// �V�[���̒ǉ�
			template<class T>
			void AddScene(const std::string& sceneName) {
				// Editor�Ƃ������O�̃V�[�����͓o�^�ł��Ȃ�
				if (sceneName == "Editor") {
					DebugLog::LogError("You cannot use the name ""Editor"" in the scene name.");
					return;
				}

				// �����V�[���������ɓo�^����Ă���ΕԂ�
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
			HRESULT SceneChange();
			// �V�[�������݂��邩�`�F�b�N
			bool IsCheckExists(const std::string& sceneName);
			// �o�^����Ă���V�[���̐���Ԃ�
			size_t GetSceneCount() const;

			// �V�[���̃^�X�N�V�X�e������
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