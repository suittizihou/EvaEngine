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

		// デフォルトコンストラクタ
		Vector3() = default;
		// コンストラクタ
		Vector3(float x, float y, float z);


		// Vector3(0, 0, 0) と同じ意味
		static Vector3 zero() { return Vector3(0.0f, 0.0f, 0.0f); }
		// Vector3(1, 1, 1) と同じ意味
		static Vector3 one() { return Vector3(1.0f, 1.0f, 1.0f); }
		// Vector3(0, 1, 0) と同じ意味
		static Vector3 up() { return Vector3(0.0f, 1.0f, 0.0f); }
		// Vector3(0, -1, 0) と同じ意味
		static Vector3 down() { return Vector3(0.0f, -1.0f, 0.0f); }
		// Vector3(-1, 0, 0) と同じ意味
		static Vector3 left() { return Vector3(-1.0f, 0.0f, 0.0f); }
		// Vector3(1, 0, 0) と同じ意味
		static Vector3 right() { return Vector3(1.0f, 0.0f, 0.0f); }
		// Vector3(0, 0, 1) と同じ意味
		static Vector3 forward() { return Vector3(0.0f, 0.0f, 1.0f); }
		// Vector3(0, 0, -1) と同じ意味
		static Vector3 back() { return Vector3(0.0f, 0.0f, -1.0f); }

		// ベクトルの長さ
		float magnitude() const;
		// magnitude を 1 としたベクトル
		Vector3 normalized() const;
		// ベクトルの2乗の長さ
		float sqr_magnitude() const;
		// [0] や[1] を使用して x や y 成分にアクセスします
		float operator[](int index) const;
		float& operator[](int index);

		// Returns true if the given vector is exactly equal to this vector.
		bool equals(const Vector3& other) const;
		// magnitude を 1 としたベクトルを作成します
		void normalize();
		// 2つのベクトルの各成分を乗算します
		void scale(const Vector3& v);
		// 既存の Vector3 に x、y、z の成分を設定します
		void set(float new_x, float new_y, float new_z);
		// ベクトルの値を見やすくフォーマットされた文字列
		std::string to_string() const;

		// 2点間（from と to）の角度を返します
		static float angle(const Vector3& from, const Vector3& to);
		// 大きさをmax_lengthまでに制限した vector のコピーを返します
		static Vector3 clamp_magnitude(const Vector3& vector, float max_length);
		// 2つのベクトルの外積
		static Vector3 cross(const Vector3& lhs, const Vector3& rhs);
		// a と b の間の距離を返します
		static float distance(const Vector3& a, const Vector3 b);
		// 2つのベクトルの内積
		static float dot(const Vector3& lhs, const Vector3& rhs);

		// 直線上にある 2 つのベクトル間を補間します
		static Vector3 lerp(const Vector3& a, const Vector3& b, float t);
		// 直線上にある 2 つのベクトル間を補間します
		static Vector3 lerp_unclamped(const Vector3& a, const Vector3& b, float t);
		// 2つのベクトルで各成分の一番大きな値を使用してベクトルを作成します
		static Vector3 max(const Vector3& lhs, const Vector3& rhs);
		// 2つのベクトルで各成分の一番小さな値を使用してベクトルを作成します
		static Vector3 min(const Vector3& lhs, const Vector3& rhs);

		// 現在の位置 current から target に向けて移動します
		static Vector3 move_towards(const Vector3& current, const Vector3& target,
			float max_distance_delta);
		// magnitude を 1 としたベクトルを作成します
		static Vector3 normalize(const Vector3& value);

		// ベクトルを別のベクトルに投影します
		static Vector3 project(const Vector3& vector, const Vector3& onNormal);
		// 平面に垂直な法線ベクトルによって定義される平面上にベクトルを射影します
		static Vector3 project_on_plane(const Vector3& vector, const Vector3& planeNormal);
		// 法線で定義された平面でベクトルを反射します
		static Vector3 reflect(const Vector3& inDirection, const Vector3& inNormal);
		// 2つのベクトルの各成分を乗算します
		static Vector3 scale(const Vector3& a, const Vector3& b);
		// 2点間（from と to）の符号付き角度を返します
		static float signed_angle(const Vector3& from, const Vector3& to, const Vector3& axis = up());

		// 目的地に向かって時間の経過とともに徐々にベクトルを変化させます
		static Vector3 smooth_damp(const Vector3& current, const Vector3& target,
			Vector3& currentVelocity, float smoothTime, float maxSpeed, float deltaTime);

		// Vector2への暗黙キャスト
		operator Vector2() const;
		// Vector2への暗黙キャスト
		operator Vector4() const;
		// Vector2への暗黙キャスト
		operator Color() const;
		// XMVECTORへの暗黙キャスト
		operator DirectX::XMVECTOR() const;
	};

	// 単項演算子オーバーロード
	Vector3 operator - (const Vector3& v);

	// 代入演算子オーバーロード
	Vector3& operator += (Vector3& lhs, const Vector3& rhs);
	Vector3& operator -= (Vector3& lhs, const Vector3& rhs);
	Vector3& operator *= (Vector3& lhs, float rhs);
	Vector3& operator /= (Vector3& lhs, float rhs);

	// ２項演算子オーバーロード
	Vector3 operator + (const Vector3& lhs, const Vector3& rhs);
	Vector3 operator - (const Vector3& lhs, const Vector3& rhs);
	Vector3 operator * (const Vector3& lhs, float rhs);
	Vector3 operator * (float lhs, const Vector3& rhs);
	Vector3 operator / (const Vector3& lhs, float rhs);

	bool operator == (const Vector3& lhs, const Vector3& rhs);
	bool operator != (const Vector3& lhs, const Vector3& rhs);
}