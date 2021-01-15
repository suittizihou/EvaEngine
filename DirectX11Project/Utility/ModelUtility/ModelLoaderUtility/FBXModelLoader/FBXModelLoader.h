#pragma once

#include <map>
#include "../ModelLoaderBase.h"

#pragma comment(lib, "libfbxsdk-md.lib")
#pragma comment(lib, "libxml2-md.lib")
#pragma comment(lib, "zlib-md.lib")

namespace fbxsdk {
	class FbxNode;
	class FbxMesh;
	class FbxSurfaceMaterial;
	class FbxFileTexture;
}

class FBXModelLoader : public ModelLoaderBase {
public:
	FBXModelLoader() = default;
	~FBXModelLoader() = default;

	My3DLib::ModelData LoadModel(const char* fileName) override;
	void LoadMaterial(fbxsdk::FbxSurfaceMaterial* material);
	bool LoadTexture(fbxsdk::FbxFileTexture* texture, std::string& keyword);
	void FindMeshNode(fbxsdk::FbxNode* node, std::map<std::string, fbxsdk::FbxNode*>& list);
	bool CreateMesh(const char* node_name, fbxsdk::FbxMesh* mesh);

private:
	My3DLib::ModelData m_Model{};
};