#pragma once

#include <string>

#ifdef EVAENGINE_EXPORTS
#define EVAENGINE_API __declspec(dllexport)
#else
#define EVAENGINE_API __declspec(dllimport)
#endif

// 2Dベクトル
struct Vector2 {
	// ベクトルのx成分
	float x{ 0.0f };
	// ベクトルのy成分
	float y{ 0.0f };

	// デフォルトコンストラクタ
	EVAENGINE_API Vector2() = default;
	// コンストラクタ
	EVAENGINE_API Vector2(float x, float y);

	// Vector2(0, 0) と同じ意味
	EVAENGINE_API static Vector2 zero();
	// Vector2(1, 1) と同じ意味
	EVAENGINE_API static Vector2 one();
	// Vector2(0, 1) と同じ意味
	EVAENGINE_API static Vector2 up();
	// Vector2(0, -1) と同じ意味
	EVAENGINE_API static Vector2 down();
	// Vector2(-1, 0) と同じ意味
	EVAENGINE_API static Vector2 left();
	// Vector2(1, 0) と同じ意味
	EVAENGINE_API static Vector2 right();

	// ベクトルの長さ（読み取り専用）
	EVAENGINE_API float magnitude() const;
	// magnitude を 1 としたベクトル（読み取り専用）
	EVAENGINE_API Vector2 normalized() const;
	//　ベクトルの 2 乗の長さを返します（読み取り専用）
	EVAENGINE_API float sqr_magnitude() const;

	// [0] や[1] を使用して x や y 成分にアクセスします
	EVAENGINE_API float operator[](int index) const;
	EVAENGINE_API float& operator[](int index);

	// ２つのベクトルが等しいか？
	EVAENGINE_API bool equals(const Vector2& other);
	// magnitude を 1 としたベクトルを作成します
	EVAENGINE_API void normalize();
	// 既存の Vector2 に x と y の成分を設定します
	EVAENGINE_API void set(float x, float y);
	// ベクトルの値を見やすくフォーマットされた文字列
	EVAENGINE_API std::string to_string() const;

	// 2つのベクトルのなす角を返します
	EVAENGINE_API static float angle(const Vector2& from, const Vector2& to);
	// 大きさを maxLength までに制限した vector のコピーを返します
	EVAENGINE_API static Vector2 clamp_magnitude(const Vector2& vector, float max_length);
	// a と b の間の距離を返します
	EVAENGINE_API static float distance(const Vector2& a, const Vector2& b);
	// 2 つのベクトルの内積
	EVAENGINE_API static float dot(const Vector2& lhs, const Vector2& rhs);

	// 2つベクトルaとbの線形補間します。
	EVAENGINE_API static Vector2 lerp(const Vector2& a, const Vector2& b, float t);
	// 2つベクトルa と b の線形補間します。
	EVAENGINE_API static Vector2 lerp_unclamped(const Vector2& a, const Vector2& b, float t);
	// 2つのベクトルで各成分の一番大きな値を使用してベクトルを作成します
	EVAENGINE_API static Vector2 max(const Vector2& lhs, const Vector2& rhs);
	// 2 つのベクトルで各成分の一番小さな値を使用してベクトルを作成します
	EVAENGINE_API static Vector2 min(const Vector2& lhs, const Vector2& rhs);
	// 現在の位置 current から target に向けて移動します
	EVAENGINE_API static Vector2 move_towards(const Vector2& current, const Vector2& target,
		float max_distance_delta);
	// この2Dベクトルに垂直な2Dベクトルを返します。
	// 正のY軸が上がる2D座標系では、結果は常に反時計回りに90度回転します。
	EVAENGINE_API static Vector2 perpendicular(Vector2 inDirection);
	// 法線を基準にしてベクトルの反射したベクトルを取得します
	EVAENGINE_API static Vector2 reflect(const Vector2& inDirection, const Vector2& inNormal);
	// 2つのベクトルの各成分を乗算します
	EVAENGINE_API static Vector2 scale(const Vector2& a, const Vector2& b);
	// Returns the signed angle in degrees between from and to.
	EVAENGINE_API static float signed_angle(const Vector2& from, const Vector2& to);
	// 目的地に向かって時間の経過とともに徐々にベクトルを変化させます
	EVAENGINE_API Vector2 smooth_damp(const Vector2& current, const Vector2& target,
		Vector2& currentVelocity, float smooth_time, float max_speed, float delta_time);
};

// 単項演算子オーバーロード
EVAENGINE_API Vector2 operator - (const Vector2& v);

// 代入演算子オーバーロード
EVAENGINE_API Vector2& operator += (Vector2& lhs, const Vector2& rhs);
EVAENGINE_API Vector2& operator -= (Vector2& lhs, const Vector2& rhs);
EVAENGINE_API Vector2& operator *= (Vector2& lhs, float rhs);
EVAENGINE_API Vector2& operator /= (Vector2& lhs, float rhs);

// ２項演算子オーバーロード
EVAENGINE_API Vector2 operator + (const Vector2& lhs, const Vector2& rhs);
EVAENGINE_API Vector2 operator - (const Vector2& lhs, const Vector2& rhs);
EVAENGINE_API Vector2 operator * (const Vector2& lhs, float rhs);
EVAENGINE_API Vector2 operator * (float lhs, const Vector2& rhs);
EVAENGINE_API Vector2 operator / (const Vector2& lhs, float rhs);

EVAENGINE_API bool operator == (const Vector2& lhs, const Vector2& rhs);
EVAENGINE_API bool operator != (const Vector2& lhs, const Vector2& rhs);