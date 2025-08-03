#pragma once

#include <guiddef.h>
#include "../GameObject/GameObjectBase.h"

namespace EvaEngine {
	typedef struct ComponentDesc {
		std::string componentName{};
		std::u8string sceneName{};
		std::weak_ptr<GameObjectBase> gameObject;
		size_t hashCode{};
		GUID guid{ GUID_NULL };
	} ComponentDesc;
}