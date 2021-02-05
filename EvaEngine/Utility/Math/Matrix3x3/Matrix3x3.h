#pragma once

// ostreamの先行宣言
#include <iosfwd>

#ifdef EVAENGINE_EXPORTS
#define EVAENGINE_API __declspec(dllexport)
#else
#define EVAENGINE_API __declspec(dllimport)
#endif

struct Vector2;

// 行列
EVAENGINE_API struct Matrix3x3 {
	float m[3][3];

	// コンストラクタ
	Matrix3x3() = default;
	// コンストラクタ
	Matrix3x3(	float m11, float m12, float m13,
				float m21, float m22, float m23,
				float m31, float m32, float m33);
	// ゼロ行列
	static Matrix3x3 zero();
	// 単位行列
	static Matrix3x3 identity();
	// 拡大縮小行列
	static Matrix3x3 scale(const Vector2& vector);
	// 回転
	static Matrix3x3 rotate(float rotation);
	// 平行移動
	static Matrix3x3 translate(const Vector2& position);
};

// 行列の加算
EVAENGINE_API Matrix3x3 operator + (const Matrix3x3& lhs, const Matrix3x3 rhs);
// 行列の減算
EVAENGINE_API Matrix3x3 operator - (const Matrix3x3& lhs, const Matrix3x3 rhs);
// 行列のスカラー倍
EVAENGINE_API Matrix3x3 operator * (const Matrix3x3& lhs, const float rhs);
// 行列のスカラー倍
EVAENGINE_API Matrix3x3 operator * (const float lhs, const Matrix3x3& rhs);
// 行列の乗算
EVAENGINE_API Matrix3x3 operator * (const Matrix3x3& lhs, const Matrix3x3 rhs);
// 行列とベクトルの積
EVAENGINE_API Vector2 operator * (const Vector2& lhs, const Matrix3x3 rhs);

// 行列の出力
EVAENGINE_API std::ostream& operator << (std::ostream& out, const Matrix3x3& rhs);