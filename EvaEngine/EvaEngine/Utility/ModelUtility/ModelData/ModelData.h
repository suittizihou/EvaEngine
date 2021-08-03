#pragma once

#include <vector>
#include <map>
#include <string>
#include "../../../Define/D3D11Defines.h"

#include "../../Mesh/Mesh.h"
#include "../../Material/Material.h"

namespace EvaEngine {
	class ModelData {
	public:
		ModelData() = default;
		~ModelData() = default;

	public:
		void Release();

	public:
		std::map<std::string, std::vector<Mesh>> meshes;
		std::map<std::string, Material> materials;
	};
}