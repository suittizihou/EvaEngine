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
    float4x4 World; // ���[���h�ϊ��s��
    float4x4 View; // �r���[�ϊ��s��
    float4x4 Projection; // �����ˉe�ϊ��s��
    float3 CameraPos; // �J�������W
    float3 LightDirection; // ���C�g����
    float3 LightColor; // ���C�g�J���[
    float3 ptPosition; // �|�C���g���C�g�̍��W
    float3 ptColor; // �|�C���g���C�g�̐F
    float ptRange; // �|�C���g���C�g�̉e���͈�
    float3 MaterialAmbient; // �A���r�G���g
    //float4 MaterialDiffuse; // �f�B�t���[�Y
    //float4 MaterialSpecular; // �X�y�L�����[
    float1 Shine;            // �X�y�L�����[�̗ݏ��
}

#endif