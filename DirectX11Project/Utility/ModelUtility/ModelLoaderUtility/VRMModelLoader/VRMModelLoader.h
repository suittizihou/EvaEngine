#pragma once

#include <DirectXMath.h>
#include <GLTFSDK/GLTF.h>

#include "../../ModelData/ModelData.h"

namespace Microsoft {
	namespace glTF {
		class Document;
		class GLTFResourceReader;
	}
}

class VRMModelLoader {
public:
	template<class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

	VRMModelLoader() = default;
	~VRMModelLoader() = default;
	ModelData::Model LoadModel(const std::string fileName);
	ModelData::Model MakeModelDataMemory(const ModelData::Model& model);

private:
	void LoadModelGeometry(const Microsoft::glTF::Document& doc, std::shared_ptr<Microsoft::glTF::GLTFResourceReader> reader);
	void MakeModelGeometry(ModelData::Model& model);
	void LoadModelMaterial(const Microsoft::glTF::Document& doc, std::shared_ptr<Microsoft::glTF::GLTFResourceReader> reader);
	void MakeModelMaterial(ModelData::Model& model);

private:
	ModelData::Model m_Model{};

};