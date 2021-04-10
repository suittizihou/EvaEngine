#pragma once

#include <d3d11.h>
#include <iostream>

namespace EvaEngine {
	class ModelLoader {
	private:
		ModelLoader() = default;
		ModelLoader(const ModelLoader&);
		ModelLoader operator=(const ModelLoader&);
		~ModelLoader() = default;

	public:
		static int Load(const std::string& fileName);
	};
}