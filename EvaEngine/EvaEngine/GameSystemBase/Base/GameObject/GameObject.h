#pragma once

#include "GameObjectBase.h"
#include "../../Manager/ComponentManager/ComponentManager.h"

namespace EvaEngine {

	class Transform;

	class GameObject final : public GameObjectBase {
	public:
		GameObject(
			const std::string& sceneName = "",
			const UINT& gameObjectID = 0,
			const std::string& tag = "",
			const std::string& name = "") :
			GameObjectBase(sceneName),
			m_GameObjectID(gameObjectID),
			m_Tag(tag),
			m_Name(name)
		{};

		~GameObject() = default;

		// ����������
		void Initialize() override;

		// ObjectID��Ԃ�
		UINT GetObjectID() const override;
		// ���O��Ԃ�
		std::string GetName() const override;
		// �^�O��Ԃ�
		std::string GetTag() const override;
		// Transform��Ԃ�
		std::weak_ptr<Transform> GetTransform();

		// �R���|�[�l���g�̓o�^
		template<class T, class... Args>
		std::weak_ptr<T> AddComponent(Args&& ... args) {
			return EvaEngine::Internal::ComponentManager::Instance().AddComponent<T>(GetSceneType(), GetGameObject(), args...);
		}

		// �R���|�[�l���g�̎擾
		template<class T>
		std::weak_ptr<T> GetComponent() {
			return EvaEngine::Internal::ComponentManager::Instance().GetComponent<T>(GetSceneType(), m_GameObjectID);
		}

		// �R���|�[�l���g�̍폜
		template<class T>
		void RemoveComponent() {
			EvaEngine::Internal::ComponentManager::Instance().RemoveComponent<T>(GetSceneType(), m_GameObjectID);
		}

		// ���O�Ō���
		std::weak_ptr<GameObject> Find(const std::string& name);
		// �^�O�Ō������ăQ�[���I�u�W�F�N�g��������Ă���
		std::weak_ptr<GameObject> FindGameObjectWithTag(const std::string& tag);
		// �^�O�Ō������ăq�b�g�����Q�[���I�u�W�F�N�g��S�������Ă���
		std::vector<std::weak_ptr<GameObject>> FindGameObjectsWithTag(const std::string& tag);

	private:
		std::weak_ptr<Transform> m_Transform;
		std::string m_Tag{};
		std::string m_Name{};
		UINT m_GameObjectID{};
	};
}