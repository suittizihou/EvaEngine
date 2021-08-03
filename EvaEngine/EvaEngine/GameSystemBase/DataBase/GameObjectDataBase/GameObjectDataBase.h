#pragma once

#include <list>
#include <memory>

#include "../../Base/GameObject/GameObject.h"

namespace EvaEngine {
	namespace Internal {
		class GameObjectDataBase {
		public:
			GameObjectDataBase() = default;
			~GameObjectDataBase() = default;

			std::weak_ptr<GameObject> Instantiate(const std::string& sceneName, const std::string& tag = "None", const std::string& name = "GameObject");
			// ���O�Ō���
			std::weak_ptr<GameObject> Find(const std::string& name);
			// �^�O�Ō������ăQ�[���I�u�W�F�N�g��������Ă���
			std::weak_ptr<GameObject> FindGameObjectWithTag(const std::string& tag);
			// �^�O�Ō������ăq�b�g�����Q�[���I�u�W�F�N�g��S�������Ă���
			std::vector<std::weak_ptr<GameObject>> FindGameObjectsWithTag(const std::string& tag);
			// �ێ����Ă���Q�[���I�u�W�F�N�g��S�폜
			void RemoveAllGameObject();

		private:
			UINT m_ObjectID{};
			std::map <std::string,	// Tag 
				std::vector<std::shared_ptr<GameObject>>> m_GameObjectList;

		};
	}
}