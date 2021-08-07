#pragma once
#include <memory>

namespace EvaEngine {
	class GameObject;
	class Transform;
	namespace Editor {
		class Selection {
			Selection() = default;
			~Selection() = default;
		public:
			static void SetActiveObject(const std::weak_ptr<GameObject>& gameObject);

		public:
			static std::weak_ptr<GameObject> activeObject;
			static std::weak_ptr<Transform> activeTransform;
			static int activeObjectID;
		};
	}
}