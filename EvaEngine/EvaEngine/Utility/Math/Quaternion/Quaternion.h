#pragma once

#include <string>
#include <DirectXMath.h>
#include "../Vector3/Vector3.h"

namespace EvaEngine {
	// �N�H�[�^�j�I��
	struct Quaternion {
		union {
			DirectX::XMFLOAT4 vec;
			float v[3];
			struct { float x, y, z, w; };
		};

		// �f�t�H���g�R���X�g���N�^
		Quaternion() = default;
		// �R���X�g���N�^
		Quaternion(float x, float y, float z, float w = 1.0f);

		// �P�ʃN�H�[�^�j�I��
		static Quaternion identity();
		// ���K��
		Quaternion normalized() const;
		// [0] ��[1] ���g�p���� x �� y �����ɃA�N�Z�X���܂�
		float operator[](int index) const;
		float& operator[](int index);

		// ������ Quaternion �� x�Ay�Az�Aw �̐�����ݒ肵�܂�
		void set(float newX, float newY, float newZ, float newW);
		// �N�H�[�^��I���̒l�����₷�������������Ԃ��܂��B
		std::string to_string() const;

		// 2 �̉�] a �� b �Ԃ̊p�x��Ԃ��܂��B
		static float angle(const Quaternion& a, const Quaternion& b);
		static Vector3 internal_make_positive(Vector3 euler);
		// axis �̎���� angle �x��]�����]���쐬���܂��B
		static Quaternion angle_axis(float angle, const Vector3& axis);
		// 2 �̉�]�̓��ς�Ԃ��܂��B
		static float dot(const Quaternion& a, const Quaternion& b);

		// �t�N�H�[�^�j�I����Ԃ��܂�
		static Quaternion inverse(const Quaternion& rotation);
		// ���K�������N�H�[�^�j�I����Ԃ��܂�
		static Quaternion normalize(const Quaternion& q);

		float length() const;

		//�@a �� b �̊Ԃ� t �ŋ���ɕ�Ԃ��܂��B�p�����[�^�[ t �́A[0, 1] �͈̔͂ł��B
		static Quaternion slerp(const Quaternion& a, const Quaternion& b, float t);
		// a �� b �̊Ԃ� t �ŋ���ɕ�Ԃ��܂��B�p�����[�^�[ t �́A�����Ă��܂���B
		static Quaternion slerp_unclamped(const Quaternion& a, const Quaternion& b, float t);

		// ��]���I�C���[�p�̒l�ŕԂ��܂�
		Vector3 euler_angles() const;
		// �I�C���[�p���N�H�[�^�j�I���ɕϊ����Ď��g�ɑ��
		void euler_angles(const Vector3& value);


		// fromDirection ���� toDirection �ւ̉�]���쐬���܂�
		void set_from_to_rotation(const Vector3& fromDirection, const Vector3& toDirection);
		// �w�肳�ꂽ forward �� upwards �����ɉ�]���܂�
		void set_look_rotation(const Vector3& view, const Vector3& up = Vector3::up());
		// ��]�����W�ɑ΂���p�x�̒l (AngleAxis) �ɕϊ����܂��B
		void to_angle_axis(float& angle, Vector3& axis);

		// z���𒆐S��z�x�Ax���𒆐S��x�x�Ay���𒆐S��y�x��]�����]��Ԃ��܂��B
		static Quaternion euler(float x, float y, float z);
		static Quaternion euler(const Vector3& euler);
		// fromDirection ���� toDirection �ւ̉�]���쐬���܂��B
		static Quaternion from_to_rotation(const Vector3& fromDirection,
			const Vector3& toDirection);
		// �w�肳�ꂽ forward �� upwards �����ɉ�]���܂�
		static Quaternion look_rotation(const Vector3& view, const Vector3& up = Vector3::up());
		// from ���� to �ւ̉�]�𓾂܂�
		static Quaternion rotate_towards(const Quaternion& from,
			const Quaternion& to, float maxDegreesDelta);
		//�@a �� b �̊Ԃ� t �Ő��`�ɕ�Ԃ��܂��B�p�����[�^�[ t �́A[0, 1] �͈̔͂ł��B
		static Quaternion lerp(const Quaternion& a, const Quaternion& b, float t);
		// a �� b �̊Ԃ� t �Ő��`�ɕ�Ԃ��܂��B�p�����[�^�[ t �́A�����Ă��܂���B
		static Quaternion lerp_unclamped(const Quaternion& a, const Quaternion& b, float t);

		// ��r(���S�ɒl����v���Ă��邩�H�j
		bool equals(const Quaternion& other) const;

		// XMVECTOR�ւ̈ÖكL���X�g
		operator DirectX::XMVECTOR() const;

	private:
		static bool is_equal_using_dot(float dot);

	public:
		static const float k_epsilon;
	};

	// ���Z�q�I�[�o�[���[�h
	Quaternion operator - (const Quaternion& q);
	Quaternion operator + (const Quaternion& lhs, const Quaternion& rhs);
	Quaternion operator - (const Quaternion& lhs, const Quaternion& rhs);
	Quaternion operator * (const Quaternion& lhs, float rhs);
	Quaternion operator * (float rhs, const Quaternion& lhs);
	Quaternion operator * (const Quaternion& lhs, const Quaternion& rhs);
	Quaternion operator / (Quaternion lhs, float s);
	Vector3 operator * (const Quaternion& rotation, const Vector3& point);
	bool operator == (const Quaternion& lhs, const Quaternion& rhs);
	bool operator != (const Quaternion& lhs, const Quaternion& rhs);
}