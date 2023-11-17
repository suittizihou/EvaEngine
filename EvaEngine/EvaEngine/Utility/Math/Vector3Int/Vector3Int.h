#pragma once

#undef min
#undef max

#include <string>
#include <DirectXMath.h>

namespace EvaEngine {
	struct Vector2Int;

	struct Vector3Int {
		union {
			DirectX::XMINT3 vec;
			int v[3];
			struct { int x, y, z; };
		};
		static const int kEpsilon;

		// �f�t�H���g�R���X�g���N�^
		Vector3Int() = default;
		// �R���X�g���N�^
		Vector3Int(int x, int y, int z);


		// Vector3Int(0, 0, 0) �Ɠ����Ӗ�
		static Vector3Int zero() { return Vector3Int(0, 0, 0); }
		// Vector3Int(1, 1, 1) �Ɠ����Ӗ�
		static Vector3Int one() { return Vector3Int(1, 1, 1); }
		// Vector3Int(0, 1, 0) �Ɠ����Ӗ�
		static Vector3Int up() { return Vector3Int(0, 1, 0); }
		// Vector3Int(0, -1, 0) �Ɠ����Ӗ�
		static Vector3Int down() { return Vector3Int(0, -1, 0); }
		// Vector3Int(-1, 0, 0) �Ɠ����Ӗ�
		static Vector3Int left() { return Vector3Int(-1, 0, 0); }
		// Vector3Int(1, 0, 0) �Ɠ����Ӗ�
		static Vector3Int right() { return Vector3Int(1, 0, 0); }
		// Vector3Int(0, 0, 1) �Ɠ����Ӗ�
		static Vector3Int forward() { return Vector3Int(0, 0, 1); }
		// Vector3Int(0, 0, -1) �Ɠ����Ӗ�
		static Vector3Int back() { return Vector3Int(0, 0, -1); }

		// �x�N�g���̒���
		int magnitude() const;
		// �x�N�g����2��̒���
		int sqr_magnitude() const;
		// [0] ��[1] ���g�p���� x �� y �����ɃA�N�Z�X���܂�
		int operator[](int index) const;
		int& operator[](int index);

		// Returns true if the given vector is exactly equal to this vector.
		bool equals(const Vector3Int& other) const;
		// 2�̃x�N�g���̊e��������Z���܂�
		void scale(const Vector3Int& v);
		// ������ Vector3Int �� x�Ay�Az �̐�����ݒ肵�܂�
		void set(int new_x, int new_y, int new_z);
		// �x�N�g���̒l�����₷���t�H�[�}�b�g���ꂽ������
		std::string to_string() const;

		// �傫����max_length�܂łɐ������� vector �̃R�s�[��Ԃ��܂�
		static Vector3Int clamp_magnitude(const Vector3Int& vector, int max_length);
		// 2�̃x�N�g���̊O��
		static Vector3Int cross(const Vector3Int& lhs, const Vector3Int& rhs);
		// a �� b �̊Ԃ̋�����Ԃ��܂�
		static int distance(const Vector3Int& a, const Vector3Int b);
		// 2�̃x�N�g���̓���
		static int dot(const Vector3Int& lhs, const Vector3Int& rhs);

		// 2�̃x�N�g���Ŋe�����̈�ԑ傫�Ȓl���g�p���ăx�N�g�����쐬���܂�
		static Vector3Int max(const Vector3Int& lhs, const Vector3Int& rhs);
		// 2�̃x�N�g���Ŋe�����̈�ԏ����Ȓl���g�p���ăx�N�g�����쐬���܂�
		static Vector3Int min(const Vector3Int& lhs, const Vector3Int& rhs);

		// 2�̃x�N�g���̊e��������Z���܂�
		static Vector3Int scale(const Vector3Int& a, const Vector3Int& b);

		// Vector2Int�ւ̈ÖكL���X�g
		operator Vector2Int() const;
		// XMVECTOR�ւ̈ÖكL���X�g
		operator DirectX::XMVECTOR() const;
	};

	// �P�����Z�q�I�[�o�[���[�h
	Vector3Int operator - (const Vector3Int& v);

	// ������Z�q�I�[�o�[���[�h
	Vector3Int& operator += (Vector3Int& lhs, const Vector3Int& rhs);
	Vector3Int& operator -= (Vector3Int& lhs, const Vector3Int& rhs);
	Vector3Int& operator *= (Vector3Int& lhs, int rhs);
	Vector3Int& operator /= (Vector3Int& lhs, int rhs);

	// �Q�����Z�q�I�[�o�[���[�h
	Vector3Int operator + (const Vector3Int& lhs, const Vector3Int& rhs);
	Vector3Int operator - (const Vector3Int& lhs, const Vector3Int& rhs);
	Vector3Int operator * (const Vector3Int& lhs, int rhs);
	Vector3Int operator * (int lhs, const Vector3Int& rhs);
	Vector3Int operator / (const Vector3Int& lhs, int rhs);

	bool operator == (const Vector3Int& lhs, const Vector3Int& rhs);
	bool operator != (const Vector3Int& lhs, const Vector3Int& rhs);
}