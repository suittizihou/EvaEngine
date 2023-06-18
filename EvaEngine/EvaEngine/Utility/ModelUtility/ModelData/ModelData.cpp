#include "ModelData.h"

void EvaEngine::ModelData::Release()
{
	for (auto& mesh : meshes) {
		for (auto& elem : mesh.second) {
			elem.Release();
		}
	}
	
	for (auto& material : materials) {
		material.second.Release();
	}
}

std::string EvaEngine::ModelData::GetFileName() const
{
	return m_FileName;
}
