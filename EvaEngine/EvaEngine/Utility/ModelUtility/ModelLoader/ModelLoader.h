#pragma once

#include <d3d11.h>
#include <iostream>
#include <memory>

namespace EvaEngine {
	class ModelData;

	class ModelLoader {
	private:
		ModelLoader() = default;
		ModelLoader(const ModelLoader&);
		ModelLoader operator=(const ModelLoader&);
		~ModelLoader() = default;

	public:
		static std::shared_ptr<ModelData> Load(const std::u8string& fileName);
	};
}