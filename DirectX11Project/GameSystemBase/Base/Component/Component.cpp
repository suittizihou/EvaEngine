#include "Component.h"
#include "../GameObject/GameObject.h"

Component::Component(
	const ComponentDesc& componentDesc,
	const UINT& functionMask,
	const bool canMultiAttach,
	const bool canRemove) :
	GameJobs(componentDesc.sceneType),
	m_GameObject(std::static_pointer_cast<GameObject>(componentDesc.gameObject.lock())),
	m_HashCode(componentDesc.hashCode),
	m_ComponentID(componentDesc.componentID),
	m_FunctionMask(functionMask),
	m_CanMultiAttach(canMultiAttach),
	m_CanRemove(canRemove),
	m_Transform(m_GameObject.lock()->GetTransform())
{
}

std::weak_ptr<GameObject> Component::GetGameObject() const
{
	return m_GameObject;
}

std::weak_ptr<Transform> Component::GetTransform() const
{
	return m_Transform;
}

bool Component::GetCanMultiAttach() const
{
	return m_CanMultiAttach;
}

bool Component::GetCanRemove() const
{
	return m_CanRemove;
}

size_t Component::GetHashCode() const
{
	return m_HashCode;
}

UINT Component::GetComponentID() const
{
	return m_ComponentID;
}

UINT Component::GetFunctionMask() const
{
	return m_FunctionMask;
}