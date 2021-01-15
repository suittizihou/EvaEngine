#pragma once

#include <d3d11.h>
#include <iostream>

class ModelLoadManager {
private:
	ModelLoadManager() = default;
	ModelLoadManager(const ModelLoadManager&);
	ModelLoadManager operator=(const ModelLoadManager&);
	~ModelLoadManager() = default;

public:
	static ModelLoadManager& Instance() {
		static ModelLoadManager instance;
		return instance;
	}

	int Load(const std::string& fileName);
};