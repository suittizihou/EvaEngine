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

		// デフォルトコンストラクタ
		Vector4() = default;
		// コンストラクタ
		Vector4(float x, float y, float z, float w);


		// Vector4(0, 0, 0, 0) と同じ意味
		static Vector4 zero() { return Vector4(0.0f, 0.0f, 0.0f, 0.0f); }
		// Vector4(1, 1, 1, 1) と同じ意味
		static Vector4 one() { return Vector4(1.0f, 1.0f, 1.0f, 1.0f); }

		// ベクトルの長さ
		float magnitude() const;
		// magnitude を 1 としたベクトル
		Vector4 normalized() const;
		// ベクトルの2乗の長さ
		float sqr_magnitude() const;
		// [0] や[1] を使用して各成分にアクセスします
		float operator[](int index) const;
		float& operator[](int index);

		// Returns true if the given vector is exactly equal to this vector.
		bool equals(const Vector4& other) const;
		// magnitude を 1 としたベクトルを作成します
		void normalize();
		// 2つのベクトルの各成分を乗算します
		void scale(const Vector4& v);
		// 既存の Vector4 に x、y、z, w の成分を設定します
		void set(float new_x, float new_y, float new_z, float new_w);
		// ベクトルの値を見やすくフォーマットされた文字列
		std::string to_string() const;

		// 2点間（from と to）の角度を返します
		static float angle(const Vector4& from, const Vector4& to);
		// 大きさをmax_lengthまでに制限した vector のコピーを返します
		static Vector4 clamp_magnitude(const Vector4& vector, float max_length);
		// a と b の間の距離を返します
		static float distance(const Vector4& a, const Vector4 b);
		// 2つのベクトルの内積
		static float dot(const Vector4& lhs, const Vector4& rhs);

		// 直線上にある 2 つのベクトル間を補間します
		static Vector4 lerp(const Vector4& a, const Vector4& b, float t);
		// 直線上にある 2 つのベクトル間を補間します
		static Vector4 lerp_unclamped(const Vector4& a, const Vector4& b, float t);
		// 2つのベクトルで各成分の一番大きな値を使用してベクトルを作成します
		static Vector4 max(const Vector4& lhs, const Vector4& rhs);
		// 2つのベクトルで各成分の一番小さな値を使用してベクトルを作成します
		static Vector4 min(const Vector4& lhs, const Vector4& rhs);

		// 現在の位置 current から target に向けて移動します
		static Vector4 move_towards(const Vector4& current, const Vector4& target,
			float max_distance_delta);
		// magnitude を 1 としたベクトルを作成します
		static Vector4 normalize(const Vector4& value);

		// ベクトルを別のベクトルに投影します
		static Vector4 project(const Vector4& vector, const Vector4& onNormal);
		// 平面に垂直な法線ベクトルによって定義される平面上にベクトルを射影します
		static Vector4 project_on_plane(const Vector4& vector, const Vector4& planeNormal);
		// 法線で定義された平面でベクトルを反射します
		static Vector4 reflect(const Vector4& inDirection, const Vector4& inNormal);
		// 2つのベクトルの各成分を乗算します
		static Vector4 scale(const Vector4& a, const Vector4& b);

		// Colorへの暗黙キャスト
		operator Color() const;
		// Vector2への暗黙キャスト
		operator Vector2() const;
		// Vector3への暗黙キャスト
		operator Vector3() const;
		// XMVECTORへの暗黙キャスト
		operator DirectX::XMVECTOR() const;
	};

	// 単項演算子オーバーロード
	Vector4 operator - (const Vector4& v);

	// 代入演算子オーバーロード
	Vector4& operator += (Vector4& lhs, const Vector4& rhs);
	Vector4& operator -= (Vector4& lhs, const Vector4& rhs);
	Vector4& operator *= (Vector4& lhs, float rhs);
	Vector4& operator /= (Vector4& lhs, float rhs);

	// ２項演算子オーバーロード
	Vector4 operator + (const Vector4& lhs, const Vector4& rhs);
	Vector4 operator - (const Vector4& lhs, const Vector4& rhs);
	Vector4 operator * (const Vector4& lhs, float rhs);
	Vector4 operator * (float lhs, const Vector4& rhs);
	Vector4 operator / (const Vector4& lhs, float rhs);

	bool operator == (const Vector4& lhs, const Vector4& rhs);
	bool operator != (const Vector4& lhs, const Vector4& rhs);
}