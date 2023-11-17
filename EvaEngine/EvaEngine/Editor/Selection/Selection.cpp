#include "Selection.h"
#include "../../GameSystemBase/Base/GameObject/GameObject.h"
#include "../../GameSystemBase/Components/Transform/Transform.h"

using namespace EvaEngine;
using namespace EvaEngine::Editor;

std::vector<std::weak_ptr<GameObject>> Selection::activeObjects;
std::vector<std::weak_ptr<Transform>> Selection::activeTransforms;
std::vector<GUID> Selection::activeObjectIDs;

void Selection::SetActiveObject(const std::weak_ptr<GameObject>& gameObject)
{
	activeObjects.clear();
	activeTransforms.clear();
	activeObjects.push_back(gameObject);
	activeTransforms.push_back(gameObject.lock()->GetTransform());
	activeObjectIDs.push_back(gameObject.lock()->GetObjectID());
}

void EvaEngine::Editor::Selection::SetActiveObjects(const std::vector<std::weak_ptr<GameObject>>& gameObjects)
{
	activeObjects.clear();
	activeTransforms.clear();
	activeObjectIDs.clear();

	activeObjects = gameObjects;
	for (int i = 0; i < activeObjects.size(); ++i) {
		activeTransforms.push_back(activeObjects[i].lock()->GetTransform());
		activeObjectIDs.push_back(activeObjects[i].lock()->GetObjectID());
	}
}

std::weak_ptr<GameObject> EvaEngine::Editor::Selection::GetActiveObject(const int index)
{
	if (activeObjects.size() == 0) return std::weak_ptr<GameObject>();
	if (activeObjects.size() >= index) return activeObjects[activeObjects.size() - 1];
	return activeObjects[index];
}

std::vector<std::weak_ptr<GameObject>> EvaEngine::Editor::Selection::GetGameObjects()
{
	return activeObjects;
}

std::weak_ptr<Transform> EvaEngine::Editor::Selection::GetActiveTransform(const int index)
{
	if (activeTransforms.size() == 0) return std::weak_ptr<Transform>();
	if (activeTransforms.size() >= index) return activeTransforms[activeTransforms.size() - 1];
	return activeTransforms[index];
}

std::vector<std::weak_ptr<Transform>> EvaEngine::Editor::Selection::GetActiveTransforms()
{
	return activeTransforms;
}

const GUID& EvaEngine::Editor::Selection::GetActiveObjectID(const int index)
{
	if (activeObjectIDs.size() == 0) return GUID_NULL;
	if (activeObjectIDs.size() >= index) return activeObjectIDs[activeObjectIDs.size() - 1];
	return activeObjectIDs[index];
}

const std::vector<GUID>& EvaEngine::Editor::Selection::GetActiveObjectIDs()
{
	return activeObjectIDs;
}
