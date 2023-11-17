#include "Component.h"
#include "../GameObject/GameObject.h"
#include "../../../Utility/GUIDUtility/GUIDUtility.h"

using namespace EvaEngine;

Component::Component(
	const UINT& functionMask,
	const bool canMultiAttach,
	const bool canRemove) :
	GameJobs(),
	m_FunctionMask(functionMask),
	m_CanMultiAttach(canMultiAttach),
	m_CanRemove(canRemove)
{
	Init();
}

void Component::SetComponentDesc(const ComponentDesc& componentDesc)
{
	m_ComponentName = componentDesc.componentName;
	SetSceneName(componentDesc.sceneName);
	m_GameObject = std::static_pointer_cast<GameObject>(componentDesc.gameObject.lock());
	m_HashCode = componentDesc.hashCode;
	m_GUID = componentDesc.guid;

	m_Transform = m_GameObject.lock()->GetTransform();
}

void EvaEngine::Component::SetIndex(const UINT index)
{
	m_Index = index;
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

const GUID& Component::GetComponentID() const
{
	return m_GUID;
}

std::string EvaEngine::Component::GetComponentIDString()
{
	return GUIDUtility::ToString(m_GUID);
}

UINT Component::GetFunctionMask() const
{
	return m_FunctionMask;
}

UINT EvaEngine::Component::GetIndex() const
{
	return m_Index;
}

std::string EvaEngine::Component::GetComponentName() const
{
	return m_ComponentName;
}
