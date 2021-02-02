#pragma once

#include <iosfwd>

#ifdef EVAENGINE_EXPORTS
#define EVAENGINE_API __declspec(dllexport)
#else
#define EVAENGINE_API __declspec(dllimport)
#endif

struct Vector3;
struct Quaternion;

// 行列
struct Matrix4x4 {
	float m[4][4]{};
	// コンストラクタ
	EVAENGINE_API Matrix4x4() = default;
	// コンストラクタ
	EVAENGINE_API Matrix4x4(
		float m11, float m12, float m13, float m14,
		float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34,
		float m41, float m42, float m43, float m44
	);

	// ゼロ行列
	EVAENGINE_API static Matrix4x4 zero();
	// 単位行列
	EVAENGINE_API static Matrix4x4 identity();
	// 逆行列
	EVAENGINE_API static Matrix4x4 inverse(const Matrix4x4& m);
	// 拡大縮小
	EVAENGINE_API static Matrix4x4 scale(const Vector3& vector);
	// クォータニオンから回転行列を求める
	EVAENGINE_API static Matrix4x4 rotate(const Quaternion& q);
	// x軸回転
	EVAENGINE_API static Matrix4x4 rotate_x(float degree);
	// y軸回転
	EVAENGINE_API static Matrix4x4 rotate_y(float degree);
	// z軸回転
	EVAENGINE_API static Matrix4x4 rotate_z(float degree);
	// 平行移動
	EVAENGINE_API static Matrix4x4 translate(const Vector3& position);

	// 視野変換行列
	EVAENGINE_API static Matrix4x4 look_at(const Vector3& eye, const Vector3& at, const Vector3& up);
	// 透視変換行列
	EVAENGINE_API static Matrix4x4 perspective(float fov, float aspect, float znear, float zfar);

	// 座標変換
	EVAENGINE_API Vector3 multply_point(const Vector3& point) const;
	// 座標変換(高速)
	EVAENGINE_API Vector3 multiply_point4x3(const Vector3& point) const;
	// ベクトル変換(平行移動行列なし)
	EVAENGINE_API Vector3 multiply_vector(const Vector3& point) const;

	// スケール値を取得
	EVAENGINE_API Vector3 scale() const;
	// 前方向ベクトル
	EVAENGINE_API Vector3 forward() const;
	// 左方法ベクトル
	EVAENGINE_API Vector3 left() const;
	// 上方向ベクトル
	EVAENGINE_API Vector3 upward() const;
	// 座標を取得
	EVAENGINE_API Vector3 position() const;
	// 回転の取得(回転行列からクォータニオンに変換)
	EVAENGINE_API Quaternion rotation() const;

	// この行列の逆行列
	EVAENGINE_API Matrix4x4 inverse() const;
	// この行列の転置行列
	EVAENGINE_API Matrix4x4 transpose() const;
	// 移動、回転やスケーリングする行列を求める
	EVAENGINE_API static Matrix4x4 TRS(const Vector3& t, const Quaternion& r, const Vector3& s);
	// この行列を移動、回転やスケーリングする行列に設定します
	EVAENGINE_API void set_TRS(const Vector3& t, const Quaternion& r, const Vector3& s);
};

// 行列の加算
EVAENGINE_API Matrix4x4 operator + (const Matrix4x4& lhs, const Matrix4x4& rhs);
// 行列の減算
EVAENGINE_API Matrix4x4 operator - (const Matrix4x4& lhs, const Matrix4x4& rhs);
// 行列のスカラー倍
EVAENGINE_API Matrix4x4 operator * (const Matrix4x4& lhs, float rhs);
// 行列のスカラー倍 
EVAENGINE_API Matrix4x4 operator * (float lhs, const Matrix4x4& rhs);
// 行列の乗算
EVAENGINE_API Matrix4x4 operator * (const Matrix4x4& lhs, const Matrix4x4& rhs);
// 行列とベクトルの積
EVAENGINE_API Vector3 operator * (const Vector3& lhs, const Matrix4x4& rhs);

// 行列の出力
EVAENGINE_API std::ostream& operator << (std::ostream& lhs, const Matrix4x4& rhs);