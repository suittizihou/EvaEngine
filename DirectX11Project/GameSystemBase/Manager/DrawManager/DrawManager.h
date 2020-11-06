#pragma once

#include "../../../Define/D3D11Defines.h"
#include "../../../Utility/ModelUtility/ModelData/ModelData.h"

class DrawManager {
public:
	// 描画開始
	static void DrawBegin();
	// 描画
	static void Draw(const My3DLib::Model& model);
	// 描画終了
	static void DrawEnd();

	// インプットレイアウトの設定
	static void SetInputLayout(ID3D11InputLayout* inputLayout);

private:
	// シェーダーのセット
	static void SetShader(const My3DLib::Material& material);
	
private:
	static InputLayout m_InputLayout;
};