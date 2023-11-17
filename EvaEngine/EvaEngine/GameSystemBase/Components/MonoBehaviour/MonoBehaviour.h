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

		// 名前で検索
		std::weak_ptr<GameObject> Find(const std::string& name);
		// タグで検索してゲームオブジェクトを一つ持ってくる
		std::weak_ptr<GameObject> FindGameObjectWithTag(const std::string& tag);
		// タグで検索してヒットしたゲームオブジェクトを全部持ってくる
		std::vector<std::weak_ptr<GameObject>> FindGameObjectsWithTag(const std::string& tag);

#if _DEBUG
		virtual void OnGUI() override {}
#endif

	private:
		std::weak_ptr<Transform> m_Transform;
	};
}