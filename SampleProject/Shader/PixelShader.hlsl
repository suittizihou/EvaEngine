#include "DefaultShaderDefine.hlsl"

Texture2D Texture : register(t0); // Texture���X���b�g0��0�Ԗڂ̃e�N�X�`�����W�X�^�ɐݒ�
SamplerState Sampler : register(s0); // Sampler���X���b�g0��0�Ԗڂ̃T���v�����W�X�^�ɐݒ�

// Lambert�g�U���ˌ����v�Z����
float3 CalcLambertDiffuse(float3 lightDirection, float3 lightColor, float3 normal)
{
    float t = max(0.0f, (dot(normal, lightDirection) * -1.0f));
    return lightColor * t;
}

// Phong���ʔ��ˌ����v�Z����
float3 CalcPhongSpecular(float3 lightDirection, float3 lightColor, float3 worldPos, float3 normal)
{
    float3 refVec = reflect(lightDirection, normal);
    float3 toEye = normalize(CameraPos - worldPos);
    float t = max(0.0f, dot(refVec, toEye));
    t = pow(t, Shine);
    return lightColor * t;
}

float3 CalcLigFromDirectionLight(PS_INPUT input)
{
    float3 diffDirection = CalcLambertDiffuse(LightDirection, LightColor, input.normal);
    float3 specDirection = CalcPhongSpecular(LightDirection, LightColor, input.worldPos, input.normal);
    return diffDirection + specDirection;
}

// �|�C���g���C�g�ɂ�锽�ˌ����v�Z
float3 CalcLigFromPointLight(PS_INPUT input)
{
    float3 ligDir = input.worldPos - ptPosition;
    ligDir = normalize(ligDir);
    float3 diffPoint = CalcLambertDiffuse(ligDir, ptColor, input.normal);
    float3 specPoint = CalcPhongSpecular(ligDir, ptColor, input.worldPos, input.normal);
    float3 distance = length(input.worldPos - ptPosition);
    float affect = max(0.0f, 1.0f - 1.0f / ptRange * distance);
    affect = pow(affect, 3.0f);
    diffPoint *= affect;
    specPoint *= affect;
    return diffPoint + specPoint;
}

// �X�|�b�g���C�g�ɂ�锽�ˌ����v�Z
float3 CalcLigFromSpotLight(PS_INPUT input)
{
    float3 ligDir = input.worldPos - spPosition;
    ligDir = normalize(ligDir);
    float3 diffSpot = CalcLambertDiffuse(ligDir, spColor, input.normal);
    float3 specSpot = CalcPhongSpecular(ligDir, spColor, input.worldPos, input.normal);
    float3 distance = length(input.worldPos - spPosition);
    float affect = max(0.0f, 1.0f - 1.0f / spRange * distance);
    affect = pow(affect, 3.0f);
    diffSpot *= affect;
    specSpot *= affect;
    float angle = dot(ligDir, spDirection);
    angle = abs(acos(angle));
    affect = max(0.0f, 1.0f - 1.0f / spAngle * angle);
    affect = pow(affect, 0.5f);
    diffSpot *= affect;
    specSpot *= affect;
    return diffSpot + specSpot;
}

float3 CalcLigFromLimLight(PS_INPUT input)
{
    float power1 = 1.0f - max(0.0f, dot(LightDirection, input.normal));
    float power2 = 1.0f - max(0.0f, input.normalInView.z * -1.0f);
    float limPower = power1 * power2;
    limPower = pow(limPower, 1.3f);
    return limPower * LightColor;
}

float4 psMain(PS_INPUT input) : SV_TARGET
{    
    // ���z�����v�Z
    float3 dirLig = CalcLigFromDirectionLight(input);
    // �|�C���g���C�g���v�Z
    float3 pointLig = CalcLigFromPointLight(input);
    // �X�|�b�g���C�g���v�Z
    float3 spotLig = CalcLigFromSpotLight(input);
    // �������C�g���v�Z
    float3 limColor = CalcLigFromLimLight(input);
    
    // ���C�g���ʂ����Z
    float3 lig = dirLig + pointLig + spotLig + limColor + MaterialAmbient;
    
    float4 outputColor = (float4)1;
    outputColor.rgb *= lig;
    return outputColor;
}