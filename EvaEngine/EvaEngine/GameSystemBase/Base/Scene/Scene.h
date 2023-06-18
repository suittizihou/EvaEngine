#pragma once

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
		void FixedUpdate();

		// �X�V����
		void Update();

		// Editor��ł����X�V����
		void ExecuteEditUpdate();

		// �x���X�V����
		void LateUpdate();

		// �`�揈��
		void Draw(ID3D11DeviceContext* command);

#if _DEBUG
		// Editor�p�̕`�揈��
		void OnGUI();
#endif

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
		std::weak_ptr<GameObject> Instantiate(const std::string& tag = "None", const std::string& name = "GameObject");

	protected:
		std::string m_SceneName{};
		UINT m_SceneID{};
	};
}