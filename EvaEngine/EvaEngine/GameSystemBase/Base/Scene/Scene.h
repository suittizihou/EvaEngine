#pragma once

#include "../../Manager/ComponentManager/ComponentManager.h"
#include "../../Manager/GameObjectManager/GameObjectManager.h"
#include "../../../GameSystemBase/Components/ComponentHeaders.h"

namespace EvaEngine {
	class Scene {
	public:
		Scene(const std::string& sceneName, const UINT sceneID) : 
			m_SceneName{ sceneName },
			m_SceneID{ sceneID }
		{};
		virtual ~Scene() = default;

	public:
		// �V�[���̏�����
		virtual void Initialize() = 0;

		// �V�[���̃A�b�v�f�[�g
		virtual void SceneUpdate() = 0;

		// �Œ�X�V����
		void FixedUpdate() {
			ComponentManager::Instance().FixedUpdate(m_SceneName);
		}

		// �X�V����
		void Update() {
			ComponentManager::Instance().Update(m_SceneName);
		};

		// �x���X�V����
		void LateUpdate() {
			ComponentManager::Instance().LateUpdate(m_SceneName);
		}

		// �`�揈��
		void Draw(const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& command)
		{
			ComponentManager::Instance().Draw(m_SceneName, command);
		};

		// ���O�Ō���
		std::weak_ptr<GameObject> Find(const std::string& name);
		// �^�O�Ō������ăQ�[���I�u�W�F�N�g��������Ă���
		std::weak_ptr<GameObject> FindGameObjectWithTag(const std::string& tag);
		// �^�O�Ō������ăq�b�g�����Q�[���I�u�W�F�N�g��S�������Ă���
		std::vector<std::weak_ptr<GameObject>> FindGameObjectsWithTag(const std::string& tag);

		// �V�[�����̎擾
		std::string GetSceneName() const;
		// �V�[����ID���擾
		UINT GetSceneID() const;

		// �Q�[���I�u�W�F�N�g�̒ǉ�
		std::weak_ptr<GameObject> AddGameObject(const std::string& tag = "None", const std::string& name = "GameObject");

	protected:
		std::string m_SceneName{};
		UINT m_SceneID{};
	};
}