#pragma once

#include "../ModelData/ModelData.h"

class ModelLoadBase {
public:
	virtual My3DLib::ModelData LoadModel(const char* fileName) = 0;
};