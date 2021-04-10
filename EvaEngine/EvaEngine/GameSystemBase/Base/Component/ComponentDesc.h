#pragma once

#include "../GameObject/GameObjectBase.h"

namespace EvaEngine {
	typedef struct ComponentDesc {
		std::string sceneName;
		std::weak_ptr<GameObjectBase> gameObject;
		size_t hashCode;
		UINT componentID;
	} ComponentDesc;
}