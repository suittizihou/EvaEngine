#pragma once

#include "../../App/DirectX11App/DirectX11App.h"
#include "../ModelUtility/ModelData/ModelData.h"
#include "../Math/Vector3/Vector3.h"

class BufferCreate {
public:
	// 頂点バッファの作成
	static bool SetVertexBuffer(std::map<std::string, std::vector<My3DLib::Mesh>>& meshMap);
	// インデックスバッファの作成
	static bool SetIndexBuffer(std::map<std::string, std::vector<My3DLib::Mesh>>& meshMap);
};