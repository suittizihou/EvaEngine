#pragma once

#include <string>
#include <list>
#include <queue>
#include <map>
#include <memory>
#include <stdexcept>
#include "../../Base/Component/Component.h"

namespace EvaEngine {
	namespace Internal {
		class ComponentDataBase {
		public:
			ComponentDataBase() = default;
			~ComponentDataBase() = default;

			// �R���|�[�l���g�̓o�^
			template<class T, class... Args>
			std::weak_ptr<T> AddComponent(const std::string& sceneName, const std::weak_ptr<GameObjectBase>& gameObject, Args&& ... args)
			{
				static_assert(std::is_base_of<Component, T>::value == true, "The argument does not inherit from Component.");

				ComponentDesc componentDesc{};
				componentDesc.sceneName = sceneName;
				componentDesc.gameObject = gameObject;
				componentDesc.hashCode = typeid(T).hash_code();
				componentDesc.componentID = m_ComponentID;
				std::shared_ptr<T> component_temp = std::make_shared<T>(args...);
				component_temp->SetComponentDesc(componentDesc);

				// �����A�^�b�`�ł��Ȃ��R���|�[�l���g�̏ꍇ
				if (!component_temp->GetCanMultiAttach()) {
					// �����R���|�[�l���g���������`�F�b�N
					for (int i = 0; i < m_Components.size(); ++i) {
						if (!IsGameObjectIDEquals(m_Components[i]->GetGameObject(), gameObject)) continue;
						if (componentDesc.hashCode != m_Components[i]->GetHashCode()) continue;

						throw std::runtime_error("Can't multi attach." + (std::string)typeid(T).name() + " : ���̃R���|�[�l���g�͕����A�^�b�`�ł��܂���");
						return std::weak_ptr<T>();
					}
				}

				// �R���|�[�l���g��ǉ�(�֐��Ȃǂ��o�^)
				AddComponent(component_temp, m_Components.size());
				// �R���|�[�l���gID���C���N�������g
				m_ComponentID += 1;

				// �R���|�[�l���g�̏����֐����Ă�
				component_temp->Awake();
				component_temp->Start();


				// �Q�Ƃ�Ԃ�
				return component_temp;
			}

			// �R���|�[�l���g�̎擾
			template<class T>
			std::weak_ptr<T> GetComponent(const UINT& gameObjectID)
			{
				size_t hashCode = typeid(T).hash_code();
				// �R���|�[�l���g����
				for (int i = 0; i < m_Components.size(); ++i) {
					// �Q�[���I�u�W�F�N�gID���Ⴄ�ꍇ�̓X�L�b�v
					if (!IsGameObjectIDEquals(m_Components[i]->GetGameObject(), gameObjectID)) continue;

					// �w�肵���R���|�[�l���g�ƃn�b�V���l���Ⴄ�ꍇ�̓R���e�B�j���[
					if (hashCode != m_Components[i]->GetHashCode()) continue;
					// dynamic_cast���g�p���Ă��Ȃ��̂͌^�ϊ��`�F�b�N�ɂ�鑬�x�ቺ��h������
					return std::static_pointer_cast<T>(m_Components[i]);
				}

				throw std::runtime_error(
					"Not found. : Name : " +
					(std::string)typeid(T).name() +
					" : " +
					std::to_string(typeid(T).hash_code()) +
					" : �R���|�[�l���g��������܂���ł���");
				return std::weak_ptr<T>();
			}

			// �R���|�[�l���g���폜
			template<class T>
			void RemoveComponent(const UINT& gameObjectID)
			{
				size_t hashCode = typeid(T).hash_code();
				for (int i = 0; i < m_Components.size(); ++i) {
					if (!IsGameObjectIDEquals(m_Components[i]->GetGameObject(), gameObjectID)) continue;
					if (hashCode != m_Components[i]->GetHashCode()) continue;

					// �����Ȃ��R���|�[�l���g�Ȃ瑁�����^�[��
					if (!m_Components[i]->GetCanRemove()) {
						throw std::runtime_error(
							"Can't remove component : " +
							(std::string)typeid(T).name() +
							" : " +
							std::to_string(typeid(T).hash_code()) +
							" : ���̃R���|�[�l���g�͏����܂���");
						return;
					}

					// �����Ώۂ̗v�f�ԍ���FunctionMask��n���ď���
					RemoveComponent(i, m_Components[i]->GetFunctionMask());
					return;

				}

				throw std::runtime_error(
					"Not found.: Name : " +
					(std::string)typeid(T).name() +
					" : " +
					std::to_string(typeid(T).hash_code()) +
					" : �R���|�[�l���g��������܂���ł���");
			}

			// �ێ����Ă���R���|�[�l���g��S���폜
			void RemoveAllComponent();

			// FixedUpdate�֐�����
			void FixedUpdate();
			// Update�֐�����
			void Update();
			// LateUpdate�֐�����
			void LateUpdate();
			// Draw�֐�����
			void Draw(
				const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& command) const;
#if _DEBUG
			void OnGUI();
#endif

		private:
			// �R���|�[�l���g��ǉ�
			void AddComponent(const std::shared_ptr<Component>& component, const int indexNum);

			// �����R���|�[�l���g�����Ɏ����Ă�������������J�E���g������
			void RemoveComponent(const int index, const UINT mask);
			// �w��̐����ɍ����������̗v�f�ԍ����擾����
			__int64 FindItr(const std::vector<int>& vec, int value);

			// �w�肳�ꂽ�Q�[���I�u�W�F�N�g�Ǝw�肳�ꂽID���������m�F����(������GameObject�̃w�b�_�[�������Əz�Q�Ƃ��������邽��cpp�ɓ�����)
			bool IsGameObjectIDEquals(const std::weak_ptr<GameObject>& obj, const UINT& id);
			bool IsGameObjectIDEquals(const std::weak_ptr<GameObject>& obj1, const std::weak_ptr<GameObjectBase>& obj2);

		private:
			// �R���|�[�l���g�̃f�[�^
			std::vector<std::shared_ptr<Component>> m_Components;

			// FixedUpdate�֐����L������Ă���R���|�[�l���g���i�[����Ă���󎚂̔ԍ����i�[����z��
			std::vector<int> m_FixedUpdateFuncNumber;

			// Update�֐����L������Ă���R���|�[�l���g���i�[����Ă���󎚂̔ԍ����i�[����z��
			std::vector<int> m_UpdateFuncNumber;

			// LateUpdate�֐����L������Ă���R���|�[�l���g���i�[����Ă���󎚂̔ԍ����i�[����z��
			std::vector<int> m_LateUpdateFuncNumber;

			// Draw�֐����L������Ă���R���|�[�l���g���i�[����Ă���󎚂̔ԍ����i�[����z��
			std::vector<int> m_DrawFuncNumber;

			UINT m_ComponentID{};
		};
	}
}