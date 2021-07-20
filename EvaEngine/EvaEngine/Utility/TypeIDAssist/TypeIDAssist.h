#pragma once
#include "../StringAssist/StringAssist.h"

#undef GetClassName

namespace EvaEngine {
	template<class T>
	class TypeIDAssist {
	public:
		static std::string GetClassName() {
			auto temp = StringAssist::Split(typeid(T).name(), "::");
			return temp[temp.size() - 1];
		}
	};
}