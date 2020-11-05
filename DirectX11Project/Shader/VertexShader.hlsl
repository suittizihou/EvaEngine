#include "PixelShader.hlsl"

struct VS_INPUT
{
    float3 Pos : POSITION;
    float3 Normal : NORMAL;
    float4 Col : COLOR;
    float2 UV : TEXCOORD;
};

PS_INPUT vsMain(VS_INPUT pos) {
	PS_INPUT o = (PS_INPUT)0;
	o.Pos = float4(pos.Pos, 1);
	o.Col = pos.Col;
	return o;
}