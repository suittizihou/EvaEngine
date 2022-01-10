#include "DefaultShaderDefine.hlsl"

Texture2D Texture : register(t0); // Texture���X���b�g0��0�Ԗڂ̃e�N�X�`�����W�X�^�ɐݒ�
SamplerState Sampler : register(s0); // Sampler���X���b�g0��0�Ԗڂ̃T���v�����W�X�^�ɐݒ�

float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal)
{
    float t = max(0.0f, (dot(normal, lightDirection) * -1.0f));
    return lightColor * t;
}

float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal)
{
    float3 refVec = reflect(lightDirection, normal);
    float3 toEye = normalize(CameraPos - worldPos);
    float t = max(0.0f, dot(refVec, toEye));
    t = pow(t, Shine);
    return lightColor * t;
}

float4 psMain(PS_INPUT input) : SV_TARGET
{    
    float3 diffDirection = CalcLambertDiffuse(LightDirection, LightColor, input.normal);
    float3 specDirection = CalcPhongSpecular(LightDirection, LightColor, input.worldPos, input.normal);

    float3 ligDir = normalize(input.worldPos - ptPosition);
    float3 diffPoint = CalcLambertDiffuse(ligDir, ptColor, input.normal);
    float3 specPoint = CalcPhongSpecular(ligDir, ptColor, input.worldPos, input.normal);

    float3 distance = length(input.worldPos - ptPosition);
    float affect = max(0.0f, 1.0f - 1.0f / ptRange * distance);
    affect = pow(affect, 3.0f);

    diffPoint *= affect;
    specPoint *= affect;
    
    float3 diffuseLig = diffPoint + diffDirection;
    float3 specularLig = specPoint + specDirection;

    float3 lig = diffuseLig + specularLig + MaterialAmbient;
    float4 outputColor = (float4)1;
    outputColor.rgb *= lig;
    return outputColor;
}