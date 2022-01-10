#include "DefaultShaderDefine.hlsl"

PS_INPUT vsMain(VS_INPUT input) {
    
    PS_INPUT output;

	// ���[�J�����W * ���[���h���W�ϊ��s��
    output.pos = mul(input.pos, World);
    output.worldPos = output.pos;
	// ���[���h���W * �r���[���W�ϊ��s��
    output.pos = mul(output.pos, View);
	// �r���[���W * �v���W�F�N�V�������W�ϊ��s��
    output.pos = mul(output.pos, Projection);
    
    float4 normal;
	// ���_�̖@���Ƀ��[���h�s����|�����킹��
	// ���[���h���W��ł̖@���̌����ɕϊ�����
    // 3�s3�� * 3�v�f�̊|���Z�̂��߁A���s�ړ��͌v�Z����Ȃ�
    output.normal = mul(World, input.normal);
    
    // ���_�F���w��
    output.col = input.col;
	// Texture�w��
    output.uv = input.uv;
    
	return output;
}