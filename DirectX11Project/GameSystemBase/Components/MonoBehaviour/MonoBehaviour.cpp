#include "MonoBehaviour.h"
#include "../../Base/GameObject/GameObject.h"
#include "../Transform/Transform.h"

MonoBehaviour::MonoBehaviour(
    const ComponentDesc& componentDesc,
    const UINT& functionMask,
    const bool canMultiAttach,
    const bool canRemove) :
    Component(componentDesc, functionMask, canMultiAttach),
    m_Transform{ GetGameObject().lock()->GetTransform() }
{
}

std::weak_ptr<Transform> MonoBehaviour::GetTransform() const
{
    return m_Transform;
}