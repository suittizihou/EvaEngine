#pragma once

#include <d3d11.h>
#include <iostream>

#ifdef EVAENGINE_EXPORTS
#define EVAENGINE_API __declspec(dllexport)
#else
#define EVAENGINE_API __declspec(dllimport)
#endif

class ModelLoadManager {
private:
	ModelLoadManager() = default;
	ModelLoadManager(const ModelLoadManager&);
	ModelLoadManager operator=(const ModelLoadManager&);
	~ModelLoadManager() = default;

public:
	EVAENGINE_API static ModelLoadManager& Instance() {
		static ModelLoadManager instance;
		return instance;
	}

	EVAENGINE_API int Load(const std::string& fileName);
};