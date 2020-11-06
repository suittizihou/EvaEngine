#pragma once

#include <DirectXMath.h>
#include "../../App/DirectX11App/DirectX11App.h"
#include "../ModelUtility/ModelData/ModelData.h"

class BufferCreate {
public:
	// 頂点バッファの作成
	static ID3D11Buffer* CreateVertexBuffer(UINT strides, std::vector<DirectX::XMFLOAT3> vertices);
	// 頂点バッファをセットする
	static bool SetVertexBuffer(std::map<std::string, std::vector<My3DLib::Mesh>>& meshMap);
	// インデックスバッファの作成
	static ID3D11Buffer* CreateIndexBuffer(UINT strides, std::vector<UINT> indices);
	// インデックスバッファをセットする
	static bool SetIndexBuffer(std::map<std::string, std::vector<My3DLib::Mesh>>& meshMap);
};