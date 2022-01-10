#pragma once

// ostreamฬๆs้พ
#include <iosfwd>
#include "../Vector3/Vector3.h"

namespace EvaEngine {

	struct Vector2;

	// s๑
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

		// RXgN^
		Matrix3x3() = default;
		// RXgN^
		Matrix3x3(float m11, float m12, float m13,
			float m21, float m22, float m23,
			float m31, float m32, float m33);
		// [s๑
		static Matrix3x3 zero();
		// Pสs๑
		static Matrix3x3 identity();
		// gๅkฌs๑
		static Matrix3x3 scale(const Vector2& vector);
		// ๑]
		static Matrix3x3 rotate(float rotation);
		// ฝsฺฎ
		static Matrix3x3 translate(const Vector2& position);

		// XMMATRIXึฬรูLXg
		operator DirectX::XMMATRIX() const;
	};

	// s๑ฬมZ
	Matrix3x3 operator + (const Matrix3x3& lhs, const Matrix3x3 rhs);
	// s๑ฬธZ
	Matrix3x3 operator - (const Matrix3x3& lhs, const Matrix3x3 rhs);
	// s๑ฬXJ[{
	Matrix3x3 operator * (const Matrix3x3& lhs, const float rhs);
	// s๑ฬXJ[{
	Matrix3x3 operator * (const float lhs, const Matrix3x3& rhs);
	// s๑ฬๆZ
	Matrix3x3 operator * (const Matrix3x3& lhs, const Matrix3x3 rhs);
	// s๑ฦxNgฬฯ
	Vector2 operator * (const Vector2& lhs, const Matrix3x3 rhs);

	// s๑ฬoอ
	std::ostream& operator << (std::ostream& out, const Matrix3x3& rhs);
}