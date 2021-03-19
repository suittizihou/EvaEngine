#pragma once

#include <DirectXMath.h>
#include "../../App/DirectX11App/DirectX11App.h"
#include "../ModelUtility/ModelData/ModelData.h"

#ifdef EVAENGINE_EXPORTS
#define __declspec(dllexport)
#else
#define __declspec(dllimport)
#endif

class BufferCreate {
public:
	// 頂点バッファの作成
	static ID3D11Buffer* CreateVertexBuffer(const std::vector<My3DLib::VertexData>& vertices, size_t strides);
	// 頂点バッファをセットする
	static bool SetVertexBuffer(std::map<std::string, std::vector<My3DLib::Mesh>>& meshMap);
	// インデックスバッファの作成
	static ID3D11Buffer* CreateIndexBuffer(const std::vector<UINT>& indices, size_t strides);
	// インデックスバッファをセットする
	static bool SetIndexBuffer(std::map<std::string, std::vector<My3DLib::Mesh>>& meshMap);
	// 定数バッファの作成
	static ID3D11Buffer* CreateConstantBuffer();
};