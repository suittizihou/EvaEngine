#ifndef MATRIX_3X3_H_
#define MATRIX_3X3_H_

// ostreamの先行宣言
#include <iosfwd>

struct Vector2;

// 行列
struct Matrix3x3 {
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
Matrix3x3 operator + (const Matrix3x3& lhs, const Matrix3x3 rhs);
// 行列の減算
Matrix3x3 operator - (const Matrix3x3& lhs, const Matrix3x3 rhs);
// 行列のスカラー倍
Matrix3x3 operator * (const Matrix3x3& lhs, const float rhs);
// 行列のスカラー倍
Matrix3x3 operator * (const float lhs, const Matrix3x3& rhs);
// 行列の乗算
Matrix3x3 operator * (const Matrix3x3& lhs, const Matrix3x3 rhs);
// 行列とベクトルの積
Vector2 operator * (const Vector2& lhs, const Matrix3x3 rhs);

// 行列の出力
std::ostream& operator << (std::ostream& out, const Matrix3x3& rhs);

#endif