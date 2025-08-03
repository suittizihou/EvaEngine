#pragma once

#include <DirectXMath.h>
#include <GLTFSDK/GLTF.h>

#include "../ModelLoadBase.h"

namespace Microsoft {
	namespace glTF {
		class Document;
		class GLTFResourceReader;
	}
}

namespace EvaEngine {
	namespace Internal {
		class VRMModelLoader : public ModelLoadBase {
		public:
			//template<class T>
			//using ComPtr = Microsoft::WRL::ComPtr<T>;

			VRMModelLoader() = default;
			~VRMModelLoader() = default;
			void LoadModel(const std::u8string& fileName, std::shared_ptr<EvaEngine::ModelData>& model) override;
			std::shared_ptr<EvaEngine::ModelData> MakeModelDataMemory(std::shared_ptr<EvaEngine::ModelData>& model);

		private:
			void LoadModelGeometry(std::shared_ptr<EvaEngine::ModelData>& model, const Microsoft::glTF::Document& doc, std::shared_ptr<Microsoft::glTF::GLTFResourceReader> reader);
			void MakeModelGeometry(std::shared_ptr<ModelData>& model);
			void LoadModelMaterial(std::shared_ptr<EvaEngine::ModelData>& model, const Microsoft::glTF::Document& doc, std::shared_ptr<Microsoft::glTF::GLTFResourceReader> reader);
			void MakeModelMaterial(std::shared_ptr<ModelData>& model);
		};
	}
}