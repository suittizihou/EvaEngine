#ifndef DEFAULT_SHADER_DEFINE_HLSL
#define DEFAULT_SHADER_DEFINE_HLSL

const float PI = 3.1415926f;

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
    float3 normalInView : TEXCOORD2; // �J������Ԃ̖@��
};

cbuffer ConstantBuffer : register(b0)
{
    float4x4 World; // ���[���h�ϊ��s��
    float4x4 View; // �r���[�ϊ��s��
    float4x4 Projection; // �����ˉe�ϊ��s��
    float3 CameraPos; // �J�������W
    float3 LightDirection; // ���C�g����
    float3 LightColor; // ���C�g�J���[
    float3 ptPosition; // �|�C���g���C�g�̍��W
    float3 ptColor; // �|�C���g���C�g�̐F
    float ptRange; // �|�C���g���C�g�̉e���͈�
    float3 spPosition;
    float3 spColor;
    float spRange;
    float3 spDirection;
    float spAngle;
    float3 MaterialAmbient; // �A���r�G���g
    float1 Shine;            // �X�y�L�����[�̗ݏ��
}

#endif