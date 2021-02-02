#pragma once

#include "../GameObject/GameObjectBase.h"

typedef struct ComponentDesc {
	SceneType sceneType;
	std::weak_ptr<GameObjectBase> gameObject;
	size_t hashCode;
	UINT componentID;
} ComponentDesc;