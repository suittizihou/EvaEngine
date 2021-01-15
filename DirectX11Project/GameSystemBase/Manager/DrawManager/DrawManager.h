#pragma once

#include "../../../Define/D3D11Defines.h"
#include "../../../Utility/ModelUtility/ModelData/ModelData.h"

class Camera;
class Transform;

class DrawManager {
public:
	// 初期化
	static void Init();

	// 描画開始
	static void DrawBegin();
	// 描画
	static void Draw(const std::weak_ptr<Camera>& camera, const std::weak_ptr<Transform>& transform, My3DLib::ModelData& model);
	// 描画終了
	static void DrawEnd();

	// マテリアルの設定
	static void SetMaterial(const My3DLib::Material& material);
	// 頂点レイアウトの設定
	static void SetVertexLayout();

	// シェーダーの設定
	static void SetShader(Shader& shader);
	static void SetShader(My3DLib::Material& material);
	// 描画するために必要な初期シェーダーを取得
	static Shader GetDefaultShader();
	
private:
	static InputLayout m_InputLayout;
	static Shader m_Shader;
};