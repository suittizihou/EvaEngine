#pragma once

#include <d3d11.h>
#include <iostream>

#ifdef EVAENGINE_EXPORTS
#define __declspec(dllexport)
#else
#define __declspec(dllimport)
#endif

class ModelLoader {
private:
	ModelLoader() = default;
	ModelLoader(const ModelLoader&);
	ModelLoader operator=(const ModelLoader&);
	~ModelLoader() = default;

public:
	static int Load(const std::string& fileName);
};