#pragma once

#undef min
#undef max

#include <string>
#include <DirectXMath.h>

namespace EvaEngine {
	struct Vector2;
	struct Vector3;
	struct Color;

	struct Vector4 {

		union {
			DirectX::XMFLOAT4 vec;
			struct { float x, y, z, w; };
			float v[4];
		};

		static const float kEpsilon;

		// �f�t�H���g�R���X�g���N�^
		Vector4() = default;
		// �R���X�g���N�^
		Vector4(float x, float y, float z, float w);


		// Vector4(0, 0, 0, 0) �Ɠ����Ӗ�
		static Vector4 zero() { return Vector4(0.0f, 0.0f, 0.0f, 0.0f); }
		// Vector4(1, 1, 1, 1) �Ɠ����Ӗ�
		static Vector4 one() { return Vector4(1.0f, 1.0f, 1.0f, 1.0f); }

		// �x�N�g���̒���
		float magnitude() const;
		// magnitude �� 1 �Ƃ����x�N�g��
		Vector4 normalized() const;
		// �x�N�g����2��̒���
		float sqr_magnitude() const;
		// [0] ��[1] ���g�p���Ċe�����ɃA�N�Z�X���܂�
		float operator[](int index) const;
		float& operator[](int index);

		// Returns true if the given vector is exactly equal to this vector.
		bool equals(const Vector4& other) const;
		// magnitude �� 1 �Ƃ����x�N�g�����쐬���܂�
		void normalize();
		// 2�̃x�N�g���̊e��������Z���܂�
		void scale(const Vector4& v);
		// ������ Vector4 �� x�Ay�Az, w �̐�����ݒ肵�܂�
		void set(float new_x, float new_y, float new_z, float new_w);
		// �x�N�g���̒l�����₷���t�H�[�}�b�g���ꂽ������
		std::string to_string() const;

		// 2�_�ԁifrom �� to�j�̊p�x��Ԃ��܂�
		static float angle(const Vector4& from, const Vector4& to);
		// �傫����max_length�܂łɐ������� vector �̃R�s�[��Ԃ��܂�
		static Vector4 clamp_magnitude(const Vector4& vector, float max_length);
		// a �� b �̊Ԃ̋�����Ԃ��܂�
		static float distance(const Vector4& a, const Vector4 b);
		// 2�̃x�N�g���̓���
		static float dot(const Vector4& lhs, const Vector4& rhs);

		// ������ɂ��� 2 �̃x�N�g���Ԃ��Ԃ��܂�
		static Vector4 lerp(const Vector4& a, const Vector4& b, float t);
		// ������ɂ��� 2 �̃x�N�g���Ԃ��Ԃ��܂�
		static Vector4 lerp_unclamped(const Vector4& a, const Vector4& b, float t);
		// 2�̃x�N�g���Ŋe�����̈�ԑ傫�Ȓl���g�p���ăx�N�g�����쐬���܂�
		static Vector4 max(const Vector4& lhs, const Vector4& rhs);
		// 2�̃x�N�g���Ŋe�����̈�ԏ����Ȓl���g�p���ăx�N�g�����쐬���܂�
		static Vector4 min(const Vector4& lhs, const Vector4& rhs);

		// ���݂̈ʒu current ���� target �Ɍ����Ĉړ����܂�
		static Vector4 move_towards(const Vector4& current, const Vector4& target,
			float max_distance_delta);
		// magnitude �� 1 �Ƃ����x�N�g�����쐬���܂�
		static Vector4 normalize(const Vector4& value);

		// �x�N�g����ʂ̃x�N�g���ɓ��e���܂�
		static Vector4 project(const Vector4& vector, const Vector4& onNormal);
		// ���ʂɐ����Ȗ@���x�N�g���ɂ���Ē�`����镽�ʏ�Ƀx�N�g�����ˉe���܂�
		static Vector4 project_on_plane(const Vector4& vector, const Vector4& planeNormal);
		// �@���Œ�`���ꂽ���ʂŃx�N�g���𔽎˂��܂�
		static Vector4 reflect(const Vector4& inDirection, const Vector4& inNormal);
		// 2�̃x�N�g���̊e��������Z���܂�
		static Vector4 scale(const Vector4& a, const Vector4& b);

		// Color�ւ̈ÖكL���X�g
		operator Color() const;
		// Vector2�ւ̈ÖكL���X�g
		operator Vector2() const;
		// Vector3�ւ̈ÖكL���X�g
		operator Vector3() const;
		// XMVECTOR�ւ̈ÖكL���X�g
		operator DirectX::XMVECTOR() const;
	};

	// �P�����Z�q�I�[�o�[���[�h
	Vector4 operator - (const Vector4& v);

	// ������Z�q�I�[�o�[���[�h
	Vector4& operator += (Vector4& lhs, const Vector4& rhs);
	Vector4& operator -= (Vector4& lhs, const Vector4& rhs);
	Vector4& operator *= (Vector4& lhs, float rhs);
	Vector4& operator /= (Vector4& lhs, float rhs);

	// �Q�����Z�q�I�[�o�[���[�h
	Vector4 operator + (const Vector4& lhs, const Vector4& rhs);
	Vector4 operator - (const Vector4& lhs, const Vector4& rhs);
	Vector4 operator * (const Vector4& lhs, float rhs);
	Vector4 operator * (float lhs, const Vector4& rhs);
	Vector4 operator / (const Vector4& lhs, float rhs);

	bool operator == (const Vector4& lhs, const Vector4& rhs);
	bool operator != (const Vector4& lhs, const Vector4& rhs);
}