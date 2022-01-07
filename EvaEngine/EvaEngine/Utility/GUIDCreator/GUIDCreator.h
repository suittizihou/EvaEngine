#pragma once
#include <string>
#include <guiddef.h>

namespace EvaEngine {
	class GUIDCreator
	{
	public:
		static bool Create(GUID& dest, const std::string& errorMessage);
	};
}
