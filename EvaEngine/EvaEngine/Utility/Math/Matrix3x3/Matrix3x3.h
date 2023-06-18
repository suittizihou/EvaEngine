#pragma once

// ostream�̐�s�錾
#include <iosfwd>
#include "../Vector3/Vector3.h"

namespace EvaEngine {

	struct Vector2;

	// �s��
	struct Matrix3x3 {

		union {
			DirectX::XMFLOAT3X3 mat;
			struct {
				float _11, _12, _13;
				float _21, _22, _23;
				float _31, _32, _33;
			};
			Vector3 v[3];
			float m[3][3];
			float m9[9];
		};

		// �R���X�g���N�^
		Matrix3x3() = default;
		// �R���X�g���N�^
		Matrix3x3(float m11, float m12, float m13,
			float m21, float m22, float m23,
			float m31, float m32, float m33);
		// �[���s��
		static Matrix3x3 zero();
		// �P�ʍs��
		static Matrix3x3 identity();
		// �g��k���s��
		static Matrix3x3 scale(const Vector2& vector);
		// ��]
		static Matrix3x3 rotate(float rotation);
		// ���s�ړ�
		static Matrix3x3 translate(const Vector2& position);

		// XMMATRIX�ւ̈ÖكL���X�g
		operator DirectX::XMMATRIX() const;
	};

	// �s��̉��Z
	Matrix3x3 operator + (const Matrix3x3& lhs, const Matrix3x3 rhs);
	// �s��̌��Z
	Matrix3x3 operator - (const Matrix3x3& lhs, const Matrix3x3 rhs);
	// �s��̃X�J���[�{
	Matrix3x3 operator * (const Matrix3x3& lhs, const float rhs);
	// �s��̃X�J���[�{
	Matrix3x3 operator * (const float lhs, const Matrix3x3& rhs);
	// �s��̏�Z
	Matrix3x3 operator * (const Matrix3x3& lhs, const Matrix3x3 rhs);
	// �s��ƃx�N�g���̐�
	Vector2 operator * (const Vector2& lhs, const Matrix3x3 rhs);

	// �s��̏o��
	std::ostream& operator << (std::ostream& out, const Matrix3x3& rhs);
}