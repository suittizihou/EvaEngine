#pragma once
#include <string>
#include <guiddef.h>

namespace EvaEngine {
	class GUIDUtility
	{
	public:
		static bool Create(GUID* dest, const std::string& errorMessage);
		static std::string ToString(const GUID& src);
	};
}
