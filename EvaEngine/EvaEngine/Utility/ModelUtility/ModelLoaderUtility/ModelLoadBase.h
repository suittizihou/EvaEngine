#pragma once

#include "../ModelData/ModelData.h"

namespace EvaEngine {
	class ModelLoadBase {
	public:
		virtual ModelData LoadModel(const char* fileName) = 0;
	};
}