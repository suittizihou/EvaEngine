#pragma once

#include <DirectXMath.h>
#include <GLTFSDK/GLTF.h>

#include "../ModelLoaderBase.h"

namespace Microsoft {
	namespace glTF {
		class Document;
		class GLTFResourceReader;
	}
}

class VRMModelLoader : public ModelLoaderBase {
public:
	template<class T>
	using ComPtr = Microsoft::WRL::ComPtr<T>;

	VRMModelLoader() = default;
	~VRMModelLoader() = default;
	My3DLib::ModelData LoadModel(const char* fileName) override;
	My3DLib::ModelData MakeModelDataMemory(const My3DLib::ModelData& model);

private:
	void LoadModelGeometry(const Microsoft::glTF::Document& doc, std::shared_ptr<Microsoft::glTF::GLTFResourceReader> reader);
	void MakeModelGeometry(My3DLib::ModelData& model);
	void LoadModelMaterial(const Microsoft::glTF::Document& doc, std::shared_ptr<Microsoft::glTF::GLTFResourceReader> reader);
	void MakeModelMaterial(My3DLib::ModelData& model);

private:
	My3DLib::ModelData m_Model{};

};