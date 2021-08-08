#pragma once
#include <memory>
#include <vector>

namespace EvaEngine {
	class GameObject;
	class Transform;
	namespace Editor {
		class Selection {
			Selection() = default;
			~Selection() = default;
		public:
			static void SetActiveObject(const std::weak_ptr<GameObject>& gameObject);
			static void SetActiveObjects(const std::vector<std::weak_ptr<GameObject>>& gameObjects);

			static std::weak_ptr<GameObject> GetActiveObject(const int index = 0);
			static std::vector<std::weak_ptr<GameObject>> GetGameObjects();

			static std::weak_ptr<Transform> GetActiveTransform(const int index = 0);
			static std::vector<std::weak_ptr<Transform>> GetActiveTransforms();

			static int GetActiveObjectID(const int index = 0);
			static std::vector<int> GetActiveObjectIDs();

		private:
			static std::vector<std::weak_ptr<GameObject>> activeObjects;
			static std::vector<std::weak_ptr<Transform>> activeTransforms;
			static std::vector<int> activeObjectIDs;
		};
	}
}