#pragma once

#include "../../Base/Component/Component.h"
#include "../../../Utility/Input/Input.h"
#include <vector>

namespace EvaEngine {
	class GameObject;
	class Transform;

	class MonoBehaviour : public Component {
	public:
		MonoBehaviour(
			const UINT& functionMask,
			const bool canMultiAttach = true,
			const bool canRemove = true);
		virtual ~MonoBehaviour() = default;

		// ���O�Ō���
		std::weak_ptr<GameObject> Find(const std::string& name);
		// �^�O�Ō������ăQ�[���I�u�W�F�N�g��������Ă���
		std::weak_ptr<GameObject> FindGameObjectWithTag(const std::string& tag);
		// �^�O�Ō������ăq�b�g�����Q�[���I�u�W�F�N�g��S�������Ă���
		std::vector<std::weak_ptr<GameObject>> FindGameObjectsWithTag(const std::string& tag);

#if _DEBUG
		virtual void OnGUI() override {}
#endif

	private:
		std::weak_ptr<Transform> m_Transform;
	};
}