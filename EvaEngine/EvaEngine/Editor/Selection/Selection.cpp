#include "Selection.h"
#include "../../GameSystemBase/Base/GameObject/GameObject.h"
#include "../../GameSystemBase/Components/Transform/Transform.h"

using namespace EvaEngine;
using namespace EvaEngine::Editor;

std::weak_ptr<GameObject> Selection::activeObject;
std::weak_ptr<Transform> Selection::activeTransform;

void Selection::SetActiveObject(const std::weak_ptr<GameObject>& gameObject)
{
	activeObject = gameObject;
	activeTransform = gameObject.lock()->GetTransform();
}