#pragma once

// ostreamの先行宣言
#include <iosfwd>
#include "../Vector3/Vector3.h"

namespace EvaEngine {

	struct Vector2;

	// 行列
	struct Matrix3x3 {

		union {
			DirectX::XMFLOAT3X3 mat;
			struct {
				float _11, _12, _13;
				float _21, _22, _23;
				float _31, _32, _33;
			};
			Vector3 v[3];
			float m[3][3];
			float m9[9];
		};

		// コンストラクタ
		Matrix3x3() = default;
		// コンストラクタ
		Matrix3x3(float m11, float m12, float m13,
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

		// XMMATRIXへの暗黙キャスト
		operator DirectX::XMMATRIX() const;
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
}