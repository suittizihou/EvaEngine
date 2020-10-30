#ifndef COMPONENT_DESC_H_
#define COMPONENT_DESC_H_

#include "../GameObject/GameObjectBase.h"

typedef struct ComponentDesc {
	SceneType sceneType;
	std::weak_ptr<GameObjectBase> gameObject;
	size_t hashCode;
	UINT componentID;
} ComponentDesc;

#endif