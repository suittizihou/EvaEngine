#pragma once

#include <d3d11.h>
#include <iostream>

#ifdef EVAENGINE_EXPORTS
#define EVAENGINE_API __declspec(dllexport)
#else
#define EVAENGINE_API __declspec(dllimport)
#endif

class ModelLoader {
private:
	ModelLoader() = default;
	ModelLoader(const ModelLoader&);
	ModelLoader operator=(const ModelLoader&);
	~ModelLoader() = default;

public:
	EVAENGINE_API static int Load(const std::string& fileName);
};