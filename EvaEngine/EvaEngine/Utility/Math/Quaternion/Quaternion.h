#pragma once

#include <string>
#include <DirectXMath.h>
#include "../Vector3/Vector3.h"

namespace EvaEngine {
	// クォータニオン
	struct Quaternion {
		union {
			DirectX::XMFLOAT4 vec;
			float v[3];
			struct { float x, y, z, w; };
		};

		// デフォルトコンストラクタ
		Quaternion() = default;
		// コンストラクタ
		Quaternion(float x, float y, float z, float w = 1.0f);

		// 単位クォータニオン
		static Quaternion identity();
		// 正規化
		Quaternion normalized() const;
		// [0] や[1] を使用して x や y 成分にアクセスします
		float operator[](int index) const;
		float& operator[](int index);

		// 既存の Quaternion に x、y、z、w の成分を設定します
		void set(float newX, float newY, float newZ, float newW);
		// クォータ二オンの値を見やすくした文字列を返します。
		std::string to_string() const;

		// 2 つの回転 a と b 間の角度を返します。
		static float angle(const Quaternion& a, const Quaternion& b);
		static Vector3 internal_make_positive(Vector3 euler);
		// axis の周りを angle 度回転する回転を作成します。
		static Quaternion angle_axis(float angle, const Vector3& axis);
		// 2 つの回転の内積を返します。
		static float dot(const Quaternion& a, const Quaternion& b);

		// 逆クォータニオンを返します
		static Quaternion inverse(const Quaternion& rotation);
		// 正規化したクォータニオンを返します
		static Quaternion normalize(const Quaternion& q);

		float length() const;

		//　a と b の間を t で球状に補間します。パラメーター t は、[0, 1] の範囲です。
		static Quaternion slerp(const Quaternion& a, const Quaternion& b, float t);
		// a と b の間を t で球状に補間します。パラメーター t は、限られていません。
		static Quaternion slerp_unclamped(const Quaternion& a, const Quaternion& b, float t);

		// 回転をオイラー角の値で返します
		Vector3 euler_angles() const;
		// オイラー角をクォータニオンに変換して自身に代入
		void euler_angles(const Vector3& value);


		// fromDirection から toDirection への回転を作成します
		void set_from_to_rotation(const Vector3& fromDirection, const Vector3& toDirection);
		// 指定された forward と upwards 方向に回転します
		void set_look_rotation(const Vector3& view, const Vector3& up = Vector3::up());
		// 回転を座標に対する角度の値 (AngleAxis) に変換します。
		void to_angle_axis(float& angle, Vector3& axis);

		// z軸を中心にz度、x軸を中心にx度、y軸を中心にy度回転する回転を返します。
		static Quaternion euler(float x, float y, float z);
		static Quaternion euler(const Vector3& euler);
		// fromDirection から toDirection への回転を作成します。
		static Quaternion from_to_rotation(const Vector3& fromDirection,
			const Vector3& toDirection);
		// 指定された forward と upwards 方向に回転します
		static Quaternion look_rotation(const Vector3& view, const Vector3& up = Vector3::up());
		// from から to への回転を得ます
		static Quaternion rotate_towards(const Quaternion& from,
			const Quaternion& to, float maxDegreesDelta);
		//　a と b の間を t で線形に補間します。パラメーター t は、[0, 1] の範囲です。
		static Quaternion lerp(const Quaternion& a, const Quaternion& b, float t);
		// a と b の間を t で線形に補間します。パラメーター t は、限られていません。
		static Quaternion lerp_unclamped(const Quaternion& a, const Quaternion& b, float t);

		// 比較(完全に値が一致しているか？）
		bool equals(const Quaternion& other) const;

		// XMVECTORへの暗黙キャスト
		operator DirectX::XMVECTOR() const;

	private:
		static bool is_equal_using_dot(float dot);

	public:
		static const float k_epsilon;
	};

	// 演算子オーバーロード
	Quaternion operator - (const Quaternion& q);
	Quaternion operator + (const Quaternion& lhs, const Quaternion& rhs);
	Quaternion operator - (const Quaternion& lhs, const Quaternion& rhs);
	Quaternion operator * (const Quaternion& lhs, float rhs);
	Quaternion operator * (float rhs, const Quaternion& lhs);
	Quaternion operator * (const Quaternion& lhs, const Quaternion& rhs);
	Quaternion operator / (Quaternion lhs, float s);
	Vector3 operator * (const Quaternion& rotation, const Vector3& point);
	bool operator == (const Quaternion& lhs, const Quaternion& rhs);
	bool operator != (const Quaternion& lhs, const Quaternion& rhs);
}