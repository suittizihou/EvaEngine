#pragma once

#include <d3d11.h>
#include <iostream>

#include "../FBXModelLoader/FBXModelLoader.h"
#include "../VRMModelLoader/VRMModelLoader.h"

class ModelLoader {
private:
	ModelLoader() = default;
	ModelLoader(const ModelLoader&);
	ModelLoader operator=(const ModelLoader&);
	~ModelLoader() = default;

public:
	static ModelLoader& Instance() {
		static ModelLoader instance;
		return instance;
	}

	int Load(const std::string& fileName);
};