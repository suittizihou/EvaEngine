#pragma once

#include <map>
#include "../../ModelData/ModelData.h"

#pragma comment(lib, "libfbxsdk-md.lib")
#pragma comment(lib, "libxml2-md.lib")
#pragma comment(lib, "zlib-md.lib")

namespace fbxsdk {
	class FbxNode;
	class FbxMesh;
}

class FBXModelLoader {
public:
	FBXModelLoader() = default;
	~FBXModelLoader() = default;

	My3DLib::Model LoadModel(const char* fileName);
	void FindMeshNode(fbxsdk::FbxNode* node, std::map<std::string, fbxsdk::FbxNode*>& list);
	bool CreateMesh(const char* node_name, fbxsdk::FbxMesh* mesh);

private:
	My3DLib::Model m_Model{};
};