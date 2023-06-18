#pragma once

#undef min
#undef max

#include <string>
#include <DirectXMath.h>

namespace EvaEngine {
	struct Vector2;
	struct Vector4;
	struct Color;
	struct Vector3 {
		union {
			DirectX::XMFLOAT3 vec;
			float v[3];
			struct { float x, y, z; };
		};
		static const float kEpsilon;

		// �f�t�H���g�R���X�g���N�^
		Vector3() = default;
		// �R���X�g���N�^
		Vector3(float x, float y, float z);


		// Vector3(0, 0, 0) �Ɠ����Ӗ�
		static Vector3 zero() { return Vector3(0.0f, 0.0f, 0.0f); }
		// Vector3(1, 1, 1) �Ɠ����Ӗ�
		static Vector3 one() { return Vector3(1.0f, 1.0f, 1.0f); }
		// Vector3(0, 1, 0) �Ɠ����Ӗ�
		static Vector3 up() { return Vector3(0.0f, 1.0f, 0.0f); }
		// Vector3(0, -1, 0) �Ɠ����Ӗ�
		static Vector3 down() { return Vector3(0.0f, -1.0f, 0.0f); }
		// Vector3(-1, 0, 0) �Ɠ����Ӗ�
		static Vector3 left() { return Vector3(-1.0f, 0.0f, 0.0f); }
		// Vector3(1, 0, 0) �Ɠ����Ӗ�
		static Vector3 right() { return Vector3(1.0f, 0.0f, 0.0f); }
		// Vector3(0, 0, 1) �Ɠ����Ӗ�
		static Vector3 forward() { return Vector3(0.0f, 0.0f, 1.0f); }
		// Vector3(0, 0, -1) �Ɠ����Ӗ�
		static Vector3 back() { return Vector3(0.0f, 0.0f, -1.0f); }

		// �x�N�g���̒���
		float magnitude() const;
		// magnitude �� 1 �Ƃ����x�N�g��
		Vector3 normalized() const;
		// �x�N�g����2��̒���
		float sqr_magnitude() const;
		// [0] ��[1] ���g�p���� x �� y �����ɃA�N�Z�X���܂�
		float operator[](int index) const;
		float& operator[](int index);

		// Returns true if the given vector is exactly equal to this vector.
		bool equals(const Vector3& other) const;
		// magnitude �� 1 �Ƃ����x�N�g�����쐬���܂�
		void normalize();
		// 2�̃x�N�g���̊e��������Z���܂�
		void scale(const Vector3& v);
		// ������ Vector3 �� x�Ay�Az �̐�����ݒ肵�܂�
		void set(float new_x, float new_y, float new_z);
		// �x�N�g���̒l�����₷���t�H�[�}�b�g���ꂽ������
		std::string to_string() const;

		// 2�_�ԁifrom �� to�j�̊p�x��Ԃ��܂�
		static float angle(const Vector3& from, const Vector3& to);
		// �傫����max_length�܂łɐ������� vector �̃R�s�[��Ԃ��܂�
		static Vector3 clamp_magnitude(const Vector3& vector, float max_length);
		// 2�̃x�N�g���̊O��
		static Vector3 cross(const Vector3& lhs, const Vector3& rhs);
		// a �� b �̊Ԃ̋�����Ԃ��܂�
		static float distance(const Vector3& a, const Vector3 b);
		// 2�̃x�N�g���̓���
		static float dot(const Vector3& lhs, const Vector3& rhs);

		// ������ɂ��� 2 �̃x�N�g���Ԃ��Ԃ��܂�
		static Vector3 lerp(const Vector3& a, const Vector3& b, float t);
		// ������ɂ��� 2 �̃x�N�g���Ԃ��Ԃ��܂�
		static Vector3 lerp_unclamped(const Vector3& a, const Vector3& b, float t);
		// 2�̃x�N�g���Ŋe�����̈�ԑ傫�Ȓl���g�p���ăx�N�g�����쐬���܂�
		static Vector3 max(const Vector3& lhs, const Vector3& rhs);
		// 2�̃x�N�g���Ŋe�����̈�ԏ����Ȓl���g�p���ăx�N�g�����쐬���܂�
		static Vector3 min(const Vector3& lhs, const Vector3& rhs);

		// ���݂̈ʒu current ���� target �Ɍ����Ĉړ����܂�
		static Vector3 move_towards(const Vector3& current, const Vector3& target,
			float max_distance_delta);
		// magnitude �� 1 �Ƃ����x�N�g�����쐬���܂�
		static Vector3 normalize(const Vector3& value);

		// �x�N�g����ʂ̃x�N�g���ɓ��e���܂�
		static Vector3 project(const Vector3& vector, const Vector3& onNormal);
		// ���ʂɐ����Ȗ@���x�N�g���ɂ���Ē�`����镽�ʏ�Ƀx�N�g�����ˉe���܂�
		static Vector3 project_on_plane(const Vector3& vector, const Vector3& planeNormal);
		// �@���Œ�`���ꂽ���ʂŃx�N�g���𔽎˂��܂�
		static Vector3 reflect(const Vector3& inDirection, const Vector3& inNormal);
		// 2�̃x�N�g���̊e��������Z���܂�
		static Vector3 scale(const Vector3& a, const Vector3& b);
		// 2�_�ԁifrom �� to�j�̕����t���p�x��Ԃ��܂�
		static float signed_angle(const Vector3& from, const Vector3& to, const Vector3& axis = up());

		// �ړI�n�Ɍ������Ď��Ԃ̌o�߂ƂƂ��ɏ��X�Ƀx�N�g����ω������܂�
		static Vector3 smooth_damp(const Vector3& current, const Vector3& target,
			Vector3& currentVelocity, float smoothTime, float maxSpeed, float deltaTime);

		// Vector2�ւ̈ÖكL���X�g
		operator Vector2() const;
		// Vector2�ւ̈ÖكL���X�g
		operator Vector4() const;
		// Vector2�ւ̈ÖكL���X�g
		operator Color() const;
		// XMVECTOR�ւ̈ÖكL���X�g
		operator DirectX::XMVECTOR() const;
	};

	// �P�����Z�q�I�[�o�[���[�h
	Vector3 operator - (const Vector3& v);

	// ������Z�q�I�[�o�[���[�h
	Vector3& operator += (Vector3& lhs, const Vector3& rhs);
	Vector3& operator -= (Vector3& lhs, const Vector3& rhs);
	Vector3& operator *= (Vector3& lhs, float rhs);
	Vector3& operator /= (Vector3& lhs, float rhs);

	// �Q�����Z�q�I�[�o�[���[�h
	Vector3 operator + (const Vector3& lhs, const Vector3& rhs);
	Vector3 operator - (const Vector3& lhs, const Vector3& rhs);
	Vector3 operator * (const Vector3& lhs, float rhs);
	Vector3 operator * (float lhs, const Vector3& rhs);
	Vector3 operator / (const Vector3& lhs, float rhs);

	bool operator == (const Vector3& lhs, const Vector3& rhs);
	bool operator != (const Vector3& lhs, const Vector3& rhs);
}