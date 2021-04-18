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

	class FBXModelLoader : public ModelLoadBase {
	public:
		FBXModelLoader() = default;
		~FBXModelLoader() = default;

		ModelData LoadModel(const char* fileName) override;
		void LoadMaterial(fbxsdk::FbxSurfaceMaterial* material);
		bool LoadTexture(fbxsdk::FbxFileTexture* texture, std::string& keyword);
		void FindMeshNode(fbxsdk::FbxNode* node, std::map<std::string, fbxsdk::FbxNode*>& list);
		bool CreateMesh(const char* node_name, fbxsdk::FbxMesh* mesh);

	private:
		ModelData m_Model{};
	};
}