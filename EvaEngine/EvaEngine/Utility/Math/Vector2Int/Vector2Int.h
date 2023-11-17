#pragma once

#include <string>
#include <DirectXMath.h>

#undef max
#undef min

namespace EvaEngine {
	struct Vector3Int;

	// 2D�x�N�g��(�����^)
	struct Vector2Int {

		union {
			DirectX::XMINT2 vec;
			struct { int x, y; };
			int v[2];
		};

		// �f�t�H���g�R���X�g���N�^
		Vector2Int() = default;
		// �R���X�g���N�^
		Vector2Int(int x, int y);

		// Vector2Int(0, 0) �Ɠ����Ӗ�
		static Vector2Int zero();
		// Vector2Int(1, 1) �Ɠ����Ӗ�
		static Vector2Int one();
		// Vector2Int(0, 1) �Ɠ����Ӗ�
		static Vector2Int up();
		// Vector2Int(0, -1) �Ɠ����Ӗ�
		static Vector2Int down();
		// Vector2Int(-1, 0) �Ɠ����Ӗ�
		static Vector2Int left();
		// Vector2Int(1, 0) �Ɠ����Ӗ�
		static Vector2Int right();

		// �x�N�g���̒����i�ǂݎ���p�j
		int magnitude() const;
		//�@�x�N�g���� 2 ��̒�����Ԃ��܂��i�ǂݎ���p�j
		int sqr_magnitude() const;

		// [0] ��[1] ���g�p���� x �� y �����ɃA�N�Z�X���܂�
		int operator[](int index) const;
		int& operator[](int index);

		// �Q�̃x�N�g�������������H
		bool equals(const Vector2Int& other);
		// ������ Vector2Int �� x �� y �̐�����ݒ肵�܂�
		void set(int x, int y);
		// �x�N�g���̒l�����₷���t�H�[�}�b�g���ꂽ������
		std::string to_string() const;

		// �傫���� maxLength �܂łɐ������� vector �̃R�s�[��Ԃ��܂�
		static Vector2Int clamp_magnitude(const Vector2Int& vector, int max_length);
		// a �� b �̊Ԃ̋�����Ԃ��܂�
		static int distance(const Vector2Int& a, const Vector2Int& b);
		// 2 �̃x�N�g���̓���
		static int dot(const Vector2Int& lhs, const Vector2Int& rhs);

		// 2�̃x�N�g���Ŋe�����̈�ԑ傫�Ȓl���g�p���ăx�N�g�����쐬���܂�
		static Vector2Int max(const Vector2Int& lhs, const Vector2Int& rhs);
		// 2 �̃x�N�g���Ŋe�����̈�ԏ����Ȓl���g�p���ăx�N�g�����쐬���܂�
		static Vector2Int min(const Vector2Int& lhs, const Vector2Int& rhs);
		// 2�̃x�N�g���̊e��������Z���܂�
		static Vector2Int scale(const Vector2Int& a, const Vector2Int& b);

		// Vector3Int�ւ̈ÖكL���X�g
		operator Vector3Int() const;
		// XMVECTOR�ւ̈ÖكL���X�g
		operator DirectX::XMVECTOR() const;
	};

	// �P�����Z�q�I�[�o�[���[�h
	Vector2Int operator - (const Vector2Int& v);

	// ������Z�q�I�[�o�[���[�h
	Vector2Int& operator += (Vector2Int& lhs, const Vector2Int& rhs);
	Vector2Int& operator -= (Vector2Int& lhs, const Vector2Int& rhs);
	Vector2Int& operator *= (Vector2Int& lhs, int rhs);
	Vector2Int& operator /= (Vector2Int& lhs, int rhs);

	// �Q�����Z�q�I�[�o�[���[�h
	Vector2Int operator + (const Vector2Int& lhs, const Vector2Int& rhs);
	Vector2Int operator - (const Vector2Int& lhs, const Vector2Int& rhs);
	Vector2Int operator * (const Vector2Int& lhs, int rhs);
	Vector2Int operator * (int lhs, const Vector2Int& rhs);
	Vector2Int operator / (const Vector2Int& lhs, int rhs);

	bool operator == (const Vector2Int& lhs, const Vector2Int& rhs);
	bool operator != (const Vector2Int& lhs, const Vector2Int& rhs);
}