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
		ModelData(const std::u8string& fileName) : m_FileName{ fileName } {};
		~ModelData() = default;

	public:
		void Release();
		std::u8string  GetFileName() const;

	public:
		std::map<std::string, std::vector<Mesh>> meshes;
		std::map<std::string, Material> materials;

	private:
		std::u8string m_FileName{};
	};
}