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

		// デフォルトコンストラクタ
		Vector3Int() = default;
		// コンストラクタ
		Vector3Int(int x, int y, int z);


		// Vector3Int(0, 0, 0) と同じ意味
		static Vector3Int zero() { return Vector3Int(0, 0, 0); }
		// Vector3Int(1, 1, 1) と同じ意味
		static Vector3Int one() { return Vector3Int(1, 1, 1); }
		// Vector3Int(0, 1, 0) と同じ意味
		static Vector3Int up() { return Vector3Int(0, 1, 0); }
		// Vector3Int(0, -1, 0) と同じ意味
		static Vector3Int down() { return Vector3Int(0, -1, 0); }
		// Vector3Int(-1, 0, 0) と同じ意味
		static Vector3Int left() { return Vector3Int(-1, 0, 0); }
		// Vector3Int(1, 0, 0) と同じ意味
		static Vector3Int right() { return Vector3Int(1, 0, 0); }
		// Vector3Int(0, 0, 1) と同じ意味
		static Vector3Int forward() { return Vector3Int(0, 0, 1); }
		// Vector3Int(0, 0, -1) と同じ意味
		static Vector3Int back() { return Vector3Int(0, 0, -1); }

		// ベクトルの長さ
		int magnitude() const;
		// ベクトルの2乗の長さ
		int sqr_magnitude() const;
		// [0] や[1] を使用して x や y 成分にアクセスします
		int operator[](int index) const;
		int& operator[](int index);

		// Returns true if the given vector is exactly equal to this vector.
		bool equals(const Vector3Int& other) const;
		// 2つのベクトルの各成分を乗算します
		void scale(const Vector3Int& v);
		// 既存の Vector3Int に x、y、z の成分を設定します
		void set(int new_x, int new_y, int new_z);
		// ベクトルの値を見やすくフォーマットされた文字列
		std::string to_string() const;

		// 大きさをmax_lengthまでに制限した vector のコピーを返します
		static Vector3Int clamp_magnitude(const Vector3Int& vector, int max_length);
		// 2つのベクトルの外積
		static Vector3Int cross(const Vector3Int& lhs, const Vector3Int& rhs);
		// a と b の間の距離を返します
		static int distance(const Vector3Int& a, const Vector3Int b);
		// 2つのベクトルの内積
		static int dot(const Vector3Int& lhs, const Vector3Int& rhs);

		// 2つのベクトルで各成分の一番大きな値を使用してベクトルを作成します
		static Vector3Int max(const Vector3Int& lhs, const Vector3Int& rhs);
		// 2つのベクトルで各成分の一番小さな値を使用してベクトルを作成します
		static Vector3Int min(const Vector3Int& lhs, const Vector3Int& rhs);

		// 2つのベクトルの各成分を乗算します
		static Vector3Int scale(const Vector3Int& a, const Vector3Int& b);

		// Vector2Intへの暗黙キャスト
		operator Vector2Int() const;
		// XMVECTORへの暗黙キャスト
		operator DirectX::XMVECTOR() const;
	};

	// 単項演算子オーバーロード
	Vector3Int operator - (const Vector3Int& v);

	// 代入演算子オーバーロード
	Vector3Int& operator += (Vector3Int& lhs, const Vector3Int& rhs);
	Vector3Int& operator -= (Vector3Int& lhs, const Vector3Int& rhs);
	Vector3Int& operator *= (Vector3Int& lhs, int rhs);
	Vector3Int& operator /= (Vector3Int& lhs, int rhs);

	// ２項演算子オーバーロード
	Vector3Int operator + (const Vector3Int& lhs, const Vector3Int& rhs);
	Vector3Int operator - (const Vector3Int& lhs, const Vector3Int& rhs);
	Vector3Int operator * (const Vector3Int& lhs, int rhs);
	Vector3Int operator * (int lhs, const Vector3Int& rhs);
	Vector3Int operator / (const Vector3Int& lhs, int rhs);

	bool operator == (const Vector3Int& lhs, const Vector3Int& rhs);
	bool operator != (const Vector3Int& lhs, const Vector3Int& rhs);
}