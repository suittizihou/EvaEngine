#pragma once

#include "../../ModelData/VertexData.h"
#include "../ModelLoadBase.h"

namespace EvaEngine {
	namespace Internal {
		class OBJModelLoader : public ModelLoadBase {
		public:

			void LoadModel(const std::u8string& fileName, std::shared_ptr<EvaEngine::ModelData>& model) override;

		private:
			bool CreateMesh(std::shared_ptr<EvaEngine::ModelData>& model, const std::u8string& fileName);
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