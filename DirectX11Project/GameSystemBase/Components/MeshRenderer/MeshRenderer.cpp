#include "MeshRenderer.h"

#include <iterator>

#include "../../Base/GameObject/GameObject.h"

#include "../MeshFilter/MeshFilter.h"
#include "../Transform/Transform.h"
#include "../Camera/Camera.h"

using namespace FunctionMask;

MeshRenderer::MeshRenderer(
	const ComponentDesc& componentDesc,
	const std::weak_ptr<MeshFilter>& meshFilter,
	const std::weak_ptr<Camera>& camera) :
	Component(componentDesc, DRAW, false),
	m_Model(meshFilter.lock()->GetModel()),
	m_MeshFilter(meshFilter),
	m_Transform(GetGameObject().lock()->GetComponent<Transform>()),
	m_Camera(camera)
{
}

void MeshRenderer::Draw(
	const Microsoft::WRL::ComPtr<ID3D11DeviceContext>& command,
	const ModelApp& modelApp)
{
	using namespace DirectX;
	using namespace Microsoft::glTF;

	// 各行列のセット.
	My3DLib::ShaderParameters constantBuffer{};

	Matrix4x4 matrix = m_Transform.lock()->local_to_world_matrix();
	XMMATRIX worldMatrix
	{
		matrix.m[0][0], matrix.m[0][1], matrix.m[0][2], matrix.m[0][3],
		matrix.m[1][0], matrix.m[1][1], matrix.m[1][2], matrix.m[1][3],
		matrix.m[2][0], matrix.m[2][1], matrix.m[2][2], matrix.m[2][3],
		matrix.m[3][0], matrix.m[3][1], matrix.m[3][2], matrix.m[3][3]
	};

	XMStoreFloat4x4(&constantBuffer.mtxWorld, XMMatrixTranspose(worldMatrix));
	XMStoreFloat4x4(&constantBuffer.mtxView, XMMatrixTranspose(m_Camera.lock()->GetViewMatrix()));
	XMStoreFloat4x4(&constantBuffer.mtxProj, XMMatrixTranspose(m_Camera.lock()->GetProjectionMatrix()));

	// 定数バッファの更新
	command->UpdateSubresource(m_ConstantBuffer.Get(), 0, NULL, &constantBuffer, 0, 0);

	// 定数バッファを設定
	command->VSSetConstantBuffers(0, 1, &m_ConstantBuffer);

	for (auto& meshs : m_Model.meshes) {

		for (auto& mesh : meshs.second) {

			UINT strides{ sizeof(My3DLib::VertexData) };
			//// 頂点・インデックスバッファ・プリミティブタイプのセット
			//command->IASetVertexBuffers(0, 1, &mesh.m_VertexBuffer, &strides, 0U);
			//command->IASetIndexBuffer(mesh.m_IndexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
			//command->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			//// このメッシュを描画
			//command->DrawIndexed(mesh.indexCount, 0, 0);
		}
	}	
}
