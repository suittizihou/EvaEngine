#include "DefaultShaderDefine.hlsl"

PS_INPUT vsMain(VS_INPUT input) {
    
    PS_INPUT output;

	// ローカル座標 * ワールド座標変換行列
    output.pos = mul(input.pos, World);
    output.worldPos = output.pos;
	// ワールド座標 * ビュー座標変換行列
    output.pos = mul(output.pos, View);
	// ビュー座標 * プロジェクション座標変換行列
    output.pos = mul(output.pos, Projection);
    
    float4 normal;
	// 頂点の法線にワールド行列を掛け合わせて
	// ワールド座標上での法線の向きに変換する
    // 3行3列 * 3要素の掛け算のため、平行移動は計算されない
    output.normal = mul(World, input.normal);
    
    // 頂点色を指定
    output.col = input.col;
	// Texture指定
    output.uv = input.uv;
    
	return output;
}