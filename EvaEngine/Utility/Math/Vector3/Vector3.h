#pragma once

#undef min
#undef max

#include <string>

#ifdef EVAENGINE_EXPORTS
#define EVAENGINE_API __declspec(dllexport)
#else
#define EVAENGINE_API __declspec(dllimport)
#endif

struct Vector3 {
	float x{ 0.0f };	// X component of the vector.
	float y{ 0.0f };	// Y component of the vector.
	float z{ 0.0f };	// Z component of the vector.

	static const float kEpsilon;

	// デフォルトコンストラクタ
	EVAENGINE_API Vector3() = default;
	// コンストラクタ
	EVAENGINE_API Vector3(float x, float y, float z);


	// Vector3(0, 0, 0) と同じ意味
	EVAENGINE_API static Vector3 zero() { return Vector3(0.0f, 0.0f, 0.0f); }
	// Vector3(1, 1, 1) と同じ意味
	EVAENGINE_API static Vector3 one() { return Vector3(1.0f, 1.0f, 1.0f); }
	// Vector3(0, 1, 0) と同じ意味
	EVAENGINE_API static Vector3 up() { return Vector3(0.0f, 1.0f, 0.0f); }
	// Vector3(0, -1, 0) と同じ意味
	EVAENGINE_API static Vector3 down() { return Vector3(0.0f, -1.0f, 0.0f); }
	// Vector3(-1, 0, 0) と同じ意味
	EVAENGINE_API static Vector3 left() { return Vector3(-1.0f, 0.0f, 0.0f); }
	// Vector3(1, 0, 0) と同じ意味
	EVAENGINE_API static Vector3 right() { return Vector3(1.0f, 0.0f, 0.0f); }
	// Vector3(0, 0, 1) と同じ意味
	EVAENGINE_API static Vector3 forward() { return Vector3(0.0f, 0.0f, 1.0f); }
	// Vector3(0, 0, -1) と同じ意味
	EVAENGINE_API static Vector3 back() { return Vector3(0.0f, 0.0f, -1.0f); }

	// ベクトルの長さ
	EVAENGINE_API float magnitude() const;
	// magnitude を 1 としたベクトル
	EVAENGINE_API Vector3 normalized() const;
	// ベクトルの2乗の長さ
	EVAENGINE_API float sqr_magnitude() const;
	// [0] や[1] を使用して x や y 成分にアクセスします
	EVAENGINE_API float operator[](int index) const;
	EVAENGINE_API float& operator[](int index);

	// Returns true if the given vector is exactly equal to this vector.
	EVAENGINE_API bool equals(const Vector3& other) const;
	// magnitude を 1 としたベクトルを作成します
	EVAENGINE_API void normalize();
	// 2つのベクトルの各成分を乗算します
	EVAENGINE_API void scale(const Vector3& v);
	// 既存の Vector3 に x、y、z の成分を設定します
	EVAENGINE_API void set(float new_x, float new_y, float new_z);
	// ベクトルの値を見やすくフォーマットされた文字列
	EVAENGINE_API std::string to_string() const;

	// 2点間（from と to）の角度を返します
	EVAENGINE_API static float angle(const Vector3& from, const Vector3& to);
	// 大きさをmax_lengthまでに制限した vector のコピーを返します
	EVAENGINE_API static Vector3 clamp_magnitude(const Vector3& vector, float max_length);
	// 2つのベクトルの外積
	EVAENGINE_API static Vector3 cross(const Vector3& lhs, const Vector3& rhs);
	// a と b の間の距離を返します
	EVAENGINE_API static float distance(const Vector3& a, const Vector3 b);
	// 2つのベクトルの内積
	EVAENGINE_API static float dot(const Vector3& lhs, const Vector3& rhs);

	// 直線上にある 2 つのベクトル間を補間します
	EVAENGINE_API static Vector3 lerp(const Vector3& a, const Vector3& b, float t);
	// 直線上にある 2 つのベクトル間を補間します
	EVAENGINE_API static Vector3 lerp_unclamped(const Vector3& a, const Vector3& b, float t);
	// 2つのベクトルで各成分の一番大きな値を使用してベクトルを作成します
	EVAENGINE_API static Vector3 max(const Vector3& lhs, const Vector3& rhs);
	// 2つのベクトルで各成分の一番小さな値を使用してベクトルを作成します
	EVAENGINE_API static Vector3 min(const Vector3& lhs, const Vector3& rhs);

	// 現在の位置 current から target に向けて移動します
	EVAENGINE_API static Vector3 move_towards(const Vector3& current, const Vector3& target,
		float max_distance_delta);
	// magnitude を 1 としたベクトルを作成します
	EVAENGINE_API static Vector3 normalize(const Vector3& value);

	// ベクトルを別のベクトルに投影します
	EVAENGINE_API static Vector3 project(const Vector3& vector, const Vector3& onNormal);
	// 平面に垂直な法線ベクトルによって定義される平面上にベクトルを射影します
	EVAENGINE_API static Vector3 project_on_plane(const Vector3& vector, const Vector3& planeNormal);
	// 法線で定義された平面でベクトルを反射します
	EVAENGINE_API static Vector3 reflect(const Vector3& inDirection, const Vector3& inNormal);
	// 2つのベクトルの各成分を乗算します
	EVAENGINE_API static Vector3 scale(const Vector3& a, const Vector3& b);
	// 2点間（from と to）の符号付き角度を返します
	EVAENGINE_API static float signed_angle(const Vector3& from, const Vector3& to, const Vector3& axis = up());

	// 目的地に向かって時間の経過とともに徐々にベクトルを変化させます
	EVAENGINE_API static Vector3 smooth_damp(const Vector3& current, const Vector3& target,
		Vector3& currentVelocity, float smoothTime, float maxSpeed, float deltaTime);
};

// 単項演算子オーバーロード
EVAENGINE_API Vector3 operator - (const Vector3& v);

// 代入演算子オーバーロード
EVAENGINE_API Vector3& operator += (Vector3& lhs, const Vector3& rhs);
EVAENGINE_API Vector3& operator -= (Vector3& lhs, const Vector3& rhs);
EVAENGINE_API Vector3& operator *= (Vector3& lhs, float rhs);
EVAENGINE_API Vector3& operator /= (Vector3& lhs, float rhs);

// ２項演算子オーバーロード
EVAENGINE_API Vector3 operator + (const Vector3& lhs, const Vector3& rhs);
EVAENGINE_API Vector3 operator - (const Vector3& lhs, const Vector3& rhs);
EVAENGINE_API Vector3 operator * (const Vector3& lhs, float rhs);
EVAENGINE_API Vector3 operator * (float lhs, const Vector3& rhs);
EVAENGINE_API Vector3 operator / (const Vector3& lhs, float rhs);

EVAENGINE_API bool operator == (const Vector3& lhs, const Vector3& rhs);
EVAENGINE_API bool operator != (const Vector3& lhs, const Vector3& rhs);