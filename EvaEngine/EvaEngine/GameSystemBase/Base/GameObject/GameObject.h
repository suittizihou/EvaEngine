#pragma once

#include "GameObjectBase.h"
#include "../../Manager/ComponentManager/ComponentManager.h"
#include "../../../System/DebugLog/DebugLog.h"

namespace EvaEngine {

	class Transform;

	class GameObject final : public GameObjectBase {
	public:
		GameObject(
			const std::string& sceneName = "",
			const GUID& guid = GUID_NULL,
			const std::string& tag = "",
			const std::string& name = "") :
			GameObjectBase(sceneName),
			m_GUID(guid),
			m_Tag(tag),
			m_Name(name)
		{};

		~GameObject() = default;

		// ����������
		void Initialize() override;

		// ObjectID��Ԃ�
		const GUID& GetObjectID() const override;
		// ���O��Ԃ�
		std::string GetName() const override;
		// �^�O��Ԃ�
		std::string GetTag() const override;
		// Transform��Ԃ�
		std::weak_ptr<Transform> GetTransform();

		// �R���|�[�l���g�̓o�^
		template<class T, class... Args>
		std::weak_ptr<T> AddComponent(Args&& ... args) {
			static_assert(std::is_base_of<Component, T>::value == true, "The argument does not inherit from Component.");
			auto component = EvaEngine::Internal::ComponentManager::Instance().AddComponent<T>(GetSceneName(), GetGameObject(), args...);
			m_Components.push_back(component);
			return component;
		}

		// �R���|�[�l���g�̎擾
		template<class T>
		std::weak_ptr<T> GetComponent() {
			return EvaEngine::Internal::ComponentManager::Instance().GetComponent<T>(GetSceneName(), GetGameObject());
		}

		std::vector<std::weak_ptr<Component>> GetAllComponents() override { return m_Components; };

		// �R���|�[�l���g�̍폜
		template<class T>
		void RemoveComponent() {
			EvaEngine::Internal::ComponentManager::Instance().RemoveComponent<T>(GetSceneName(), m_GUID);
			
			// �Q�Ƃ��؂ꂽ�R���|�[�l���g��z�񂩂�폜
			for (int i = 0; i < m_Components.size(); ++i)
			{
				if (m_Components[i].expired()) {
					// �����ꏊ�Ɩ������N�����Ɠ���ւ�
					std::iter_swap(m_Components.begin() + i, m_Components.end() - 1);
					// �������폜
					m_Components.pop_back();
					return;
				}
			}

			DebugLog::LogError("GameObject����Component�폜�Ɏ��s���܂����B");
		}

		// ���O�Ō���
		std::weak_ptr<GameObject> Find(const std::string& name);
		// �^�O�Ō������ăQ�[���I�u�W�F�N�g��������Ă���
		std::weak_ptr<GameObject> FindGameObjectWithTag(const std::string& tag);
		// �^�O�Ō������ăq�b�g�����Q�[���I�u�W�F�N�g��S�������Ă���
		std::vector<std::weak_ptr<GameObject>> FindGameObjectsWithTag(const std::string& tag);
		// �I�u�W�F�N�g�̃A�N�e�B�u��Ԃ�ݒ�
		void SetActive(const bool active);
		// �I�u�W�F�N�g�̃A�N�e�B�u��Ԃ��擾
		bool ActiveSelf() const;

	private:
		std::vector<std::weak_ptr<Component>> m_Components;
		std::weak_ptr<Transform> m_Transform;
		std::string m_Tag{};
		std::string m_Name{};
		bool m_IsActive{ true };
		GUID m_GUID{};
	};
}