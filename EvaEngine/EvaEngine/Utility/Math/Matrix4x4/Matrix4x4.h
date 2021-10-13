#pragma once

#include <iosfwd>
#include <DirectXMath.h>

namespace EvaEngine {

	struct Vector3;
	struct Quaternion;

	// 行列
	struct Matrix4x4 {

		union{
			float m[4][4];
			float m16[16];
		};

		// コンストラクタ
		Matrix4x4() = default;
		// コンストラクタ
		Matrix4x4(
			float m11, float m12, float m13, float m14,
			float m21, float m22, float m23, float m24,
			float m31, float m32, float m33, float m34,
			float m41, float m42, float m43, float m44
		);
		Matrix4x4(float* matrix);
		Matrix4x4(const Matrix4x4& matrix) { memcpy(&m16[0], &matrix.m16[0], sizeof(float) * 16); }

		operator float* () { return m16; }
		operator const float* () const { return m16; }

		// ゼロ行列
		static Matrix4x4 zero();
		// 単位行列
		static Matrix4x4 identity();
		// 逆行列
		static Matrix4x4 inverse(const Matrix4x4& m);
		// 拡大縮小
		static Matrix4x4 scale(const Vector3& vector);
		// クォータニオンから回転行列を求める
		static Matrix4x4 rotate(const Quaternion& q);
		// x軸回転
		static Matrix4x4 rotate_x(float degree);
		// y軸回転
		static Matrix4x4 rotate_y(float degree);
		// z軸回転
		static Matrix4x4 rotate_z(float degree);
		// 平行移動
		static Matrix4x4 translate(const Vector3& position);

		// 視野変換行列
		static Matrix4x4 look_at(const Vector3& eye, const Vector3& at, const Vector3& up);
		// 透視変換行列
		static Matrix4x4 perspective(float fov, float aspect, float znear, float zfar);

		// 座標変換
		Vector3 multply_point(const Vector3& point) const;
		// 座標変換(高速)
		Vector3 multiply_point4x3(const Vector3& point) const;
		// ベクトル変換(平行移動行列なし)
		Vector3 multiply_vector(const Vector3& point) const;

		// スケール値を取得
		Vector3 scale() const;
		// 前方向ベクトル
		Vector3 forward() const;
		// 左方法ベクトル
		Vector3 left() const;
		// 上方向ベクトル
		Vector3 upward() const;
		// 座標を取得
		Vector3 position() const;
		// 回転の取得(回転行列からクォータニオンに変換)
		Quaternion rotation() const;

		// この行列の逆行列
		Matrix4x4 inverse() const;
		// この行列の転置行列
		Matrix4x4 transpose() const;
		// 移動、回転やスケーリングする行列を求める
		static Matrix4x4 TRS(const Vector3& t, const Quaternion& r, const Vector3& s);
		// この行列を移動、回転やスケーリングする行列に設定します
		void set_TRS(const Vector3& t, const Quaternion& r, const Vector3& s);

		// Matrix4x4をDirectXMathのXMATRIXに変換する
		DirectX::XMMATRIX to_XMMATRIX() const;
		static DirectX::XMMATRIX to_XMMATRIX(const Matrix4x4& matrix);
		// DirectXMathのXMATRIXをMatrix4x4に変換する
		static Matrix4x4 to_Matrix4x4(const DirectX::XMMATRIX& matrix);
	};

	// 行列の加算
	Matrix4x4 operator + (const Matrix4x4& lhs, const Matrix4x4& rhs);
	// 行列の減算
	Matrix4x4 operator - (const Matrix4x4& lhs, const Matrix4x4& rhs);
	// 行列のスカラー倍
	Matrix4x4 operator * (const Matrix4x4& lhs, float rhs);
	// 行列のスカラー倍 
	Matrix4x4 operator * (float lhs, const Matrix4x4& rhs);
	// 行列の乗算
	Matrix4x4 operator * (const Matrix4x4& lhs, const Matrix4x4& rhs);
	// 行列とベクトルの積
	Vector3 operator * (const Vector3& lhs, const Matrix4x4& rhs);

	// 行列の出力
	std::ostream& operator << (std::ostream& lhs, const Matrix4x4& rhs);
}