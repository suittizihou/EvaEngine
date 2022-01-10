#ifndef DEFAULT_SHADER_DEFINE_HLSL
#define DEFAULT_SHADER_DEFINE_HLSL

struct VS_INPUT
{
    float4 pos : POSITION;
    float3 normal : NORMAL;
    float4 col : COLOR;
    float2 uv : TEXCOORD;
};

struct PS_INPUT
{
    float4 pos : SV_POSITION;
    float3 normal : NORMAL;
    float4 col : COLOR;
    float2 uv : TEXCOORD;
    float3 worldPos : TEXCOORD1;
};

cbuffer ConstantBuffer
{
    float4x4 World; // ワールド変換行列
    float4x4 View; // ビュー変換行列
    float4x4 Projection; // 透視射影変換行列
    float3 CameraPos; // カメラ座標
    float3 LightDirection; // ライト方向
    float3 LightColor; // ライトカラー
    float3 ptPosition; // ポイントライトの座標
    float3 ptColor; // ポイントライトの色
    float ptRange; // ポイントライトの影響範囲
    float3 MaterialAmbient; // アンビエント
    //float4 MaterialDiffuse; // ディフューズ
    //float4 MaterialSpecular; // スペキュラー
    float1 Shine;            // スペキュラーの累乗回数
}

#endif