#pragma once

#include <iosfwd>
#include <DirectXMath.h>
#include "../Vector4/Vector4.h"

namespace EvaEngine {
	struct Vector3;
	struct Quaternion;

	// �s��
	struct Matrix4x4 {

		union {
			DirectX::XMFLOAT4X4 mat;
			struct {
				float _11, _12, _13, _14;
				float _21, _22, _23, _24;
				float _31, _32, _33, _34;
				float _41, _42, _43, _44;
			};
			Vector4 v[4];
			float m[4][4];
			float m16[16];
		};

		// �R���X�g���N�^
		Matrix4x4() = default;
		// �R���X�g���N�^
		Matrix4x4(
			float m11, float m12, float m13, float m14,
			float m21, float m22, float m23, float m24,
			float m31, float m32, float m33, float m34,
			float m41, float m42, float m43, float m44
		);
		Matrix4x4(float* matrix);

		// �[���s��
		static Matrix4x4 zero();
		// �P�ʍs��
		static Matrix4x4 identity();
		// �t�s��
		static Matrix4x4 inverse(const Matrix4x4& m);
		// �g��k��
		static Matrix4x4 scale(const Vector3& vector);
		// �N�H�[�^�j�I�������]�s������߂�
		static Matrix4x4 rotate(const Quaternion& q);
		// x����]
		static Matrix4x4 rotate_x(float degree);
		// y����]
		static Matrix4x4 rotate_y(float degree);
		// z����]
		static Matrix4x4 rotate_z(float degree);
		// ���s�ړ�
		static Matrix4x4 translate(const Vector3& position);

		// ����ϊ��s��
		static Matrix4x4 look_at(const Vector3& eye, const Vector3& at, const Vector3& up);
		// �����ϊ��s��
		static Matrix4x4 perspective(float fov, float aspect, float znear, float zfar);

		// ���W�ϊ�
		Vector3 multply_point(const Vector3& point) const;
		// ���W�ϊ�(����)
		Vector3 multiply_point4x3(const Vector3& point) const;
		// �x�N�g���ϊ�(���s�ړ��s��Ȃ�)
		Vector3 multiply_vector(const Vector3& point) const;

		// �X�P�[���l���擾
		Vector3 scale() const;
		// �O�����x�N�g��
		Vector3 forward() const;
		// �����@�x�N�g��
		Vector3 left() const;
		// ������x�N�g��
		Vector3 upward() const;
		// ���W���擾
		Vector3 position() const;
		// ��]�̎擾(��]�s�񂩂�N�H�[�^�j�I���ɕϊ�)
		Quaternion rotation() const;

		// ���̍s��̋t�s��
		Matrix4x4 inverse() const;
		// ���̍s��̓]�u�s��
		Matrix4x4 transpose() const;
		// �ړ��A��]��X�P�[�����O����s������߂�
		static Matrix4x4 TRS(const Vector3& t, const Quaternion& r, const Vector3& s);
		// ���̍s����ړ��A��]��X�P�[�����O����s��ɐݒ肵�܂�
		void set_TRS(const Vector3& t, const Quaternion& r, const Vector3& s);

		// DirectXMath��XMATRIX��Matrix4x4�ɕϊ�����
		static Matrix4x4 to_Matrix4x4(const DirectX::XMMATRIX& matrix);

		operator DirectX::XMMATRIX() const;
	};

	// �s��̉��Z
	Matrix4x4 operator + (const Matrix4x4& lhs, const Matrix4x4& rhs);
	// �s��̌��Z
	Matrix4x4 operator - (const Matrix4x4& lhs, const Matrix4x4& rhs);
	// �s��̃X�J���[�{
	Matrix4x4 operator * (const Matrix4x4& lhs, float rhs);
	// �s��̃X�J���[�{ 
	Matrix4x4 operator * (float lhs, const Matrix4x4& rhs);
	// �s��̏�Z
	Matrix4x4 operator * (const Matrix4x4& lhs, const Matrix4x4& rhs);
	// �s��ƃx�N�g���̐�
	Vector3 operator * (const Vector3& lhs, const Matrix4x4& rhs);

	// �s��̏o��
	std::ostream& operator << (std::ostream& lhs, const Matrix4x4& rhs);
}