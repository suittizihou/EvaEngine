#pragma once

#include <map>
#include "../ModelLoadBase.h"

//#if _DEBUG
//#pragma comment(lib, "libfbxsdk-md.lib")
//#pragma comment(lib, "libxml2-md.lib")
//#pragma comment(lib, "zlib-md.lib")
//#elif NDEBUG
//#pragma comment(lib, "libfbxsdk-mt.lib")
//#pragma comment(lib, "libxml2-mt.lib")
//#pragma comment(lib, "zlib-mt.lib")
//#endif

namespace fbxsdk {
	class FbxNode;
	class FbxMesh;
	class FbxSurfaceMaterial;
	class FbxFileTexture;
}

namespace EvaEngine {
	namespace Internal {
		class FBXModelLoader : public ModelLoadBase {
		public:
			FBXModelLoader() = default;
			~FBXModelLoader() = default;

			void LoadModel(const std::u8string& fileName, std::shared_ptr<EvaEngine::ModelData>& model) override;
			void LoadMaterial(std::shared_ptr<EvaEngine::ModelData>& model, fbxsdk::FbxSurfaceMaterial* material);
			bool LoadTexture(std::shared_ptr<EvaEngine::ModelData>& model, fbxsdk::FbxFileTexture* texture, std::string& keyword);
			void FindMeshNode(fbxsdk::FbxNode* node, std::map<std::string, fbxsdk::FbxNode*>& list);
			bool CreateMesh(std::shared_ptr<EvaEngine::ModelData>& model, const char* node_name, fbxsdk::FbxMesh* mesh);
		};
	}
}