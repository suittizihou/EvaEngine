#pragma once
#include "../StringAssist/StringAssist.h"

#undef GetClassName

namespace EvaEngine {
	template<class T>
	class TypeIDAssist {
		TypeIDAssist() = default;
		~TypeIDAssist() = default;
	public:
		static std::string GetClassName() {
			auto temp = StringAssist::Split(typeid(T).name(), "::");
			if (temp.size() <= 1) temp = StringAssist::Split(typeid(T).name(), " ");
			return reinterpret_cast<const char*>(&temp[temp.size() - 1]);
		}

		static std::u8string GetClassNameU8() {
			auto temp = StringAssist::Split(typeid(T).name(), "::");
			if (temp.size() <= 1) temp = StringAssist::Split(typeid(T).name(), " ");
			return temp[temp.size() - 1];
		}
	};
}