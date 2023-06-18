#pragma once
#include <string>
#include <guiddef.h>

namespace std {
	template<>
	struct hash<GUID>
	{
		size_t operator()(const GUID& guid) const noexcept {
			const std::uint64_t* p = reinterpret_cast<const std::uint64_t*> (&guid);
			std::hash<std::uint64_t> hash;
			return hash(p[0]) ^ hash(p[1]);
		}
	};
}

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
