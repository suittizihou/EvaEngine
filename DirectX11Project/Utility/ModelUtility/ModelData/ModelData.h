#pragma once

#include <vector>
#include <map>
#include <string>
#include "../../../Define/D3D11Defines.h"

#include "../../Mesh/Mesh.h"
#include "../../Material/Material.h"

namespace My3DLib {
	class ModelData {
	public:
		ModelData() = default;
		~ModelData() = default;

		std::map<std::string, std::vector<My3DLib::Mesh>> meshes;
		std::map<std::string, My3DLib::Material> materials;
	};
}