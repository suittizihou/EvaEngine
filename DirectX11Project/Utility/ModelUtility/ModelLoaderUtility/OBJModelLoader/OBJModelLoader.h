#pragma once

#include "../../ModelData/VertexData.h"
#include "../ModelLoaderBase.h"

class OBJModelLoader : public ModelLoaderBase {
public:

	My3DLib::ModelData LoadModel(const char* fileName) override;

private:
	bool CreateMesh(My3DLib::ModelData& model, const char* fileName);
	void ParseVKeywordTag(std::vector<DirectX::XMFLOAT3>& data, char* buffer);
	
	void ParseFKeywordTag(
		_Out_ std::vector<My3DLib::VertexData>& outVertexData,
		_Out_ std::vector<unsigned int>& outIndices,
		std::vector<DirectX::XMFLOAT3>& vertices,
		std::vector<DirectX::XMFLOAT3>& normals, 
		char* buffer);

	void ParseShashKeywordTag(int* list, char* buffer);
};