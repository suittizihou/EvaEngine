#pragma once

#include <string>
#include <DirectXMath.h>

#undef max
#undef min

namespace EvaEngine {
	struct Vector3Int;

	// 2Dベクトル(整数型)
	struct Vector2Int {

		union {
			DirectX::XMINT2 vec;
			struct { int x, y; };
			int v[2];
		};

		// デフォルトコンストラクタ
		Vector2Int() = default;
		// コンストラクタ
		Vector2Int(int x, int y);

		// Vector2Int(0, 0) と同じ意味
		static Vector2Int zero();
		// Vector2Int(1, 1) と同じ意味
		static Vector2Int one();
		// Vector2Int(0, 1) と同じ意味
		static Vector2Int up();
		// Vector2Int(0, -1) と同じ意味
		static Vector2Int down();
		// Vector2Int(-1, 0) と同じ意味
		static Vector2Int left();
		// Vector2Int(1, 0) と同じ意味
		static Vector2Int right();

		// ベクトルの長さ（読み取り専用）
		int magnitude() const;
		//　ベクトルの 2 乗の長さを返します（読み取り専用）
		int sqr_magnitude() const;

		// [0] や[1] を使用して x や y 成分にアクセスします
		int operator[](int index) const;
		int& operator[](int index);

		// ２つのベクトルが等しいか？
		bool equals(const Vector2Int& other);
		// 既存の Vector2Int に x と y の成分を設定します
		void set(int x, int y);
		// ベクトルの値を見やすくフォーマットされた文字列
		std::string to_string() const;

		// 大きさを maxLength までに制限した vector のコピーを返します
		static Vector2Int clamp_magnitude(const Vector2Int& vector, int max_length);
		// a と b の間の距離を返します
		static int distance(const Vector2Int& a, const Vector2Int& b);
		// 2 つのベクトルの内積
		static int dot(const Vector2Int& lhs, const Vector2Int& rhs);

		// 2つのベクトルで各成分の一番大きな値を使用してベクトルを作成します
		static Vector2Int max(const Vector2Int& lhs, const Vector2Int& rhs);
		// 2 つのベクトルで各成分の一番小さな値を使用してベクトルを作成します
		static Vector2Int min(const Vector2Int& lhs, const Vector2Int& rhs);
		// 2つのベクトルの各成分を乗算します
		static Vector2Int scale(const Vector2Int& a, const Vector2Int& b);

		// Vector3Intへの暗黙キャスト
		operator Vector3Int() const;
		// XMVECTORへの暗黙キャスト
		operator DirectX::XMVECTOR() const;
	};

	// 単項演算子オーバーロード
	Vector2Int operator - (const Vector2Int& v);

	// 代入演算子オーバーロード
	Vector2Int& operator += (Vector2Int& lhs, const Vector2Int& rhs);
	Vector2Int& operator -= (Vector2Int& lhs, const Vector2Int& rhs);
	Vector2Int& operator *= (Vector2Int& lhs, int rhs);
	Vector2Int& operator /= (Vector2Int& lhs, int rhs);

	// ２項演算子オーバーロード
	Vector2Int operator + (const Vector2Int& lhs, const Vector2Int& rhs);
	Vector2Int operator - (const Vector2Int& lhs, const Vector2Int& rhs);
	Vector2Int operator * (const Vector2Int& lhs, int rhs);
	Vector2Int operator * (int lhs, const Vector2Int& rhs);
	Vector2Int operator / (const Vector2Int& lhs, int rhs);

	bool operator == (const Vector2Int& lhs, const Vector2Int& rhs);
	bool operator != (const Vector2Int& lhs, const Vector2Int& rhs);
}