#pragma once

#include "../../../Define/D3D11Defines.h"
#include "../../../Utility/ModelUtility/ModelData/ModelData.h"

namespace EvaEngine {

	class Camera;
	class Transform;

	class DrawManager {
	public:
		// 初期化
		static HRESULT Init();

		// 描画開始
		static void DrawBegin();
		// 描画
		static void Draw(
			const std::weak_ptr<Camera>& camera,
			const std::weak_ptr<Transform>& transform,
			ModelData& model);

		// 描画終了
		static void DrawEnd();

		// マテリアルの設定
		static void SetMaterial(Material& material);
		// 頂点レイアウトの設定
		static void SetVertexLayout();

		// シェーダーの設定
		static void SetShader(Shader& shader);
		static void SetShader(Material& material);
		// 描画するために必要な初期シェーダーを取得
		static Shader GetDefaultShader();

	private:
		static InputLayout m_InputLayout;
		static Shader m_Shader;
	};
}