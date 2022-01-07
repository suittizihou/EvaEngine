#pragma once
#include <string>
#include <guiddef.h>

namespace EvaEngine {
	struct GUIDComparer {
		bool operator()(const GUID& lfs, const GUID& rhs) const { return memcmp(&lfs, &rhs, sizeof(rhs)) < 0; }
	};

	class GUIDUtility
	{
	public:
		static bool Create(GUID* dest, const std::string& errorMessage);
		static std::string ToString(const GUID& src);
	};
}
