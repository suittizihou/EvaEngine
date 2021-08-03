#pragma once

#include "../../ModelData/VertexData.h"
#include "../ModelLoadBase.h"

namespace EvaEngine {
	namespace Internal {
		class OBJModelLoader : public ModelLoadBase {
		public:

			ModelData LoadModel(const char* fileName) override;

		private:
			bool CreateMesh(EvaEngine::ModelData& model, const char* fileName);
			void ParseVKeywordTag(std::vector<DirectX::XMFLOAT3>& data, char* buffer);

			void ParseFKeywordTag(
				_Out_ std::vector<EvaEngine::VertexData>& outVertexData,
				_Out_ std::vector<unsigned int>& outIndices,
				std::vector<DirectX::XMFLOAT3>& vertices,
				std::vector<DirectX::XMFLOAT3>& normals,
				char* buffer);

			void ParseShashKeywordTag(int* list, char* buffer);
		};
	}
}