#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
#include <GLTFSDK/GLTF.h>
#include <wrl.h>
#include <vector>
#include <map>
#include "../../../Define/D3D11Defines.h"

#include "../../Mesh/Mesh.h"
#include "../../Material/Material.h"

namespace My3DLib {

	class ModelData {
	public:
		template<class T>
		using ComPtr = Microsoft::WRL::ComPtr<T>;

		ModelData() = default;
		~ModelData() = default;

		struct VertexData {
			DirectX::XMFLOAT3 position;		// 座標(x, y, z)
			DirectX::XMFLOAT4 color;		// 頂点カラー
			//DirectX::XMFLOAT3 normal;		// 法線
			//DirectX::XMFLOAT2 texture;		// テクスチャ座標(u, v)
		};

		struct ShaderParameters {
			DirectX::XMFLOAT4X4 mtxWorld;
			DirectX::XMFLOAT4X4 mtxView;
			DirectX::XMFLOAT4X4 mtxProj;
		};

		struct BufferObject {
			ComPtr<ID3D11Buffer> buffer;
			union {
				D3D11_BUFFER_DESC vertexView;
				D3D11_BUFFER_DESC indexView;
			};
		};

		//struct TextureObject {
		//	ComPtr<ID3D11Texture2D> texture;
		//	DXGI_FORMAT format;
		//};

		struct Model {
			std::map<std::string, std::vector<Mesh>> meshes;
			std::map<std::string, std::vector<Material>> materials;
		};
	};
}