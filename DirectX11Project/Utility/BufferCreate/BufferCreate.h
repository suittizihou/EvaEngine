#pragma once

#include "../../App/DirectX11App/DirectX11App.h"
#include "../ModelUtility/ModelData/ModelData.h"

class BufferCreate {
public:
	// 頂点バッファの作成
	static ID3D11Buffer* CreateVertexBuffer(ModelData::VertexData* vertexData, UINT vertexNum);
	// インデックスバッファの作成
	static ID3D11Buffer* CreateIndexBuffer(UINT* index, UINT indexNum);
};