#pragma once

#include "../Vector3/Vector3.h"
#include <string>

#ifdef EVAENGINE_EXPORTS
#define EVAENGINE_API __declspec(dllexport)
#else
#define EVAENGINE_API __declspec(dllimport)
#endif

// クォータニオン
struct Quaternion {
	float x{ 0.0f };
	float y{ 0.0f };
	float z{ 0.0f };
	float w{ 1.0f };

	// デフォルトコンストラクタ
	EVAENGINE_API Quaternion() = default;
	// コンストラクタ
	EVAENGINE_API Quaternion(float x, float y, float z, float w);

	// 単位クォータニオン
	EVAENGINE_API static Quaternion identity();
	// 正規化
	EVAENGINE_API Quaternion normalized() const;
	// [0] や[1] を使用して x や y 成分にアクセスします
	EVAENGINE_API float operator[](int index) const;
	EVAENGINE_API float& operator[](int index);

	// 既存の Quaternion に x、y、z、w の成分を設定します
	EVAENGINE_API void set(float newX, float newY, float newZ, float newW);
	// クォータ二オンの値を見やすくした文字列を返します。
	EVAENGINE_API std::string to_string() const;

	// 2 つの回転 a と b 間の角度を返します。
	EVAENGINE_API static float angle(const Quaternion& a, const Quaternion& b);
	EVAENGINE_API static Vector3 internal_make_positive(Vector3 euler);
	// axis の周りを angle 度回転する回転を作成します。
	EVAENGINE_API static Quaternion angle_axis(float angle, const Vector3& axis);
	// 2 つの回転の内積を返します。
	EVAENGINE_API static float dot(const Quaternion& a, const Quaternion& b);

	// 逆クォータニオンを返します
	EVAENGINE_API static Quaternion inverse(const Quaternion& rotation);
	// 正規化したクォータニオンを返します
	EVAENGINE_API static Quaternion normalize(const Quaternion& q);

	EVAENGINE_API float length() const;

	//　a と b の間を t で球状に補間します。パラメーター t は、[0, 1] の範囲です。
	EVAENGINE_API static Quaternion slerp(const Quaternion& a, const Quaternion& b, float t);
	// a と b の間を t で球状に補間します。パラメーター t は、限られていません。
	EVAENGINE_API static Quaternion slerp_unclamped(const Quaternion& a, const Quaternion& b, float t);

	// 回転をオイラー角の値で返します
	EVAENGINE_API Vector3 euler_angles() const;
	// オイラー角をクォータニオンに変換して自身に代入
	EVAENGINE_API void euler_angles(const Vector3& value);


	// fromDirection から toDirection への回転を作成します
	EVAENGINE_API void set_from_to_rotation(const Vector3& fromDirection, const Vector3& toDirection);
	// 指定された forward と upwards 方向に回転します
	EVAENGINE_API void set_look_rotation(const Vector3& view, const Vector3& up = Vector3::up());
	// 回転を座標に対する角度の値 (AngleAxis) に変換します。
	EVAENGINE_API void to_angle_axis(float& angle, Vector3& axis);

	// z軸を中心にz度、x軸を中心にx度、y軸を中心にy度回転する回転を返します。
	EVAENGINE_API static Quaternion euler(float x, float y, float z);
	EVAENGINE_API static Quaternion euler(const Vector3& euler);
	// fromDirection から toDirection への回転を作成します。
	EVAENGINE_API static Quaternion from_to_rotation(const Vector3& fromDirection,
		const Vector3& toDirection);
	// 指定された forward と upwards 方向に回転します
	EVAENGINE_API static Quaternion look_rotation(const Vector3& view, const Vector3& up = Vector3::up());
	// from から to への回転を得ます
	EVAENGINE_API static Quaternion rotate_towards(const Quaternion& from,
		const Quaternion& to, float maxDegreesDelta);
	//　a と b の間を t で線形に補間します。パラメーター t は、[0, 1] の範囲です。
	EVAENGINE_API static Quaternion lerp(const Quaternion& a, const Quaternion& b, float t);
	// a と b の間を t で線形に補間します。パラメーター t は、限られていません。
	EVAENGINE_API static Quaternion lerp_unclamped(const Quaternion& a, const Quaternion& b, float t);

	// 比較(完全に値が一致しているか？）
	EVAENGINE_API bool equals(const Quaternion& other) const;

private:
	static bool is_equal_using_dot(float dot);

public:
	static const float k_epsilon;
};

// 演算子オーバーロード
EVAENGINE_API Quaternion operator - (const Quaternion& q);
EVAENGINE_API Quaternion operator + (const Quaternion& lhs, const Quaternion& rhs);
EVAENGINE_API Quaternion operator - (const Quaternion& lhs, const Quaternion& rhs);
EVAENGINE_API Quaternion operator * (const Quaternion& lhs, float rhs);
EVAENGINE_API Quaternion operator * (float rhs, const Quaternion& lhs);
EVAENGINE_API Quaternion operator * (const Quaternion& lhs, const Quaternion& rhs);
EVAENGINE_API Quaternion operator / (Quaternion lhs, float s);
EVAENGINE_API Vector3 operator * (const Quaternion& rotation, const Vector3& point);
EVAENGINE_API bool operator == (const Quaternion& lhs, const Quaternion& rhs);
EVAENGINE_API bool operator != (const Quaternion& lhs, const Quaternion& rhs);