#pragma once

#include "../ModelData/ModelData.h"

namespace EvaEngine {
	namespace Internal {
		class ModelLoadBase {
		public:
			virtual void LoadModel(const char* fileName, std::shared_ptr<EvaEngine::ModelData>& model) = 0;
		};
	}
}