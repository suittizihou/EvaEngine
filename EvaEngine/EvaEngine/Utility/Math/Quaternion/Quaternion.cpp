#include <cmath>
#include "Quaternion.h"
#include "../Vector3/Vector3.h"
#include "..//Mathf/Mathf.h"

float kEpsilon = 0.000001f;

using namespace EvaEngine;

Quaternion::Quaternion(float x, float y, float z, float w) :
	x{ x },
	y{ y },
	z{ z },
	w{ w }
{
}

Quaternion Quaternion::identity()
{
	return Quaternion{ 0.0f, 0.0f, 0.0f, 1.0f };
}

Quaternion Quaternion::normalized() const
{
	float len = length();
	if (len < 0.000001f) {
		return Quaternion::identity();
	}
	return *this / len;
}

float Quaternion::operator[](int index) const
{
	switch (index) {
	case 0: return x;
	case 1: return y;
	case 2: return z;
	case 3: return w;
	default:
		throw "配列の境界外";
	}
}

float& Quaternion::operator[](int index)
{
	switch (index) {
	case 0: return x;
	case 1: return y;
	case 2: return z;
	case 3: return w;
	default:
		throw "配列の境界外";
	}
}

void Quaternion::set(float newX, float newY, float newZ, float newW)
{
	x = newX;
	y = newY;
	z = newZ;
	w = newW;
}

std::string Quaternion::to_string() const
{
	return "x : " + std::to_string(x) +
		"y : " + std::to_string(y) +
		"z : " + std::to_string(z) +
		"w : " + std::to_string(w);
}

float Quaternion::angle(const Quaternion& a, const Quaternion& b)
{
	float temp_dot = dot(a, b);
	return is_equal_using_dot(temp_dot) ? 0.0f : std::acos(Mathf::min(std::abs(temp_dot), 1.0f)) * 2.0f * Mathf::rad_to_deg();
}

Vector3 Quaternion::internal_make_positive(Vector3 euler)
{
	float negativeFlip = -0.0001f * Mathf::rad_to_deg();
	float positiveFlip = 360.0f + negativeFlip;

	if (euler.x < negativeFlip)
		euler.x += 360.0f;
	else if (euler.x > positiveFlip)
		euler.x -= 360.0f;

	if (euler.y < negativeFlip)
		euler.y += 360.0f;
	else if (euler.y > positiveFlip)
		euler.y -= 360.0f;

	if (euler.z < negativeFlip)
		euler.z += 360.0f;
	else if (euler.z > positiveFlip)
		euler.z -= 360.0f;

	return euler;
}

Quaternion Quaternion::angle_axis(float angle, const Vector3& axis)
{
	Vector3 v = axis.normalized();
	angle *= Mathf::deg_to_rad();
	float s = std::sin(angle * 0.5f) / axis.magnitude();

	float x = s * v.x;
	float y = s * v.y;
	float z = s * v.z;
	float w = std::cos(angle * 0.5f);

	return Quaternion(x, y, z, w);
}

float Quaternion::dot(const Quaternion& a, const Quaternion& b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
}

Quaternion Quaternion::inverse(const Quaternion& rotation)
{
	return Quaternion(-rotation.x, -rotation.y, -rotation.z, rotation.w);
}

Quaternion Quaternion::normalize(const Quaternion& q)
{
	return q.normalized();
}

float Quaternion::length() const
{
	return std::sqrt(dot(*this, *this));
}

Quaternion Quaternion::slerp(const Quaternion& a, const Quaternion& b, float t)
{
	t = Mathf::clamp(t, 0, 1);
	return slerp_unclamped(a, b, t);
}

Quaternion Quaternion::slerp_unclamped(const Quaternion& a, const Quaternion& b, float t)
{
	float cos = dot(a, b);
	Quaternion t2 = b;
	if (cos < 0.0f) {
		cos = -cos;
		t2 = -b;
	}
	float k0 = 1.0f - t;
	float k1 = t;
	if (cos < 0.999f) {
		float theta = std::acos(cos);
		k0 = std::sin(theta * k0) / std::sin(theta);
		k1 = std::sin(theta * k1) / std::sin(theta);
	}
	return (a * k0) + (t2 * k1);
}

Vector3 Quaternion::euler_angles() const
{
	Vector3 ax = *this * Vector3(1.0f, 0.0f, 0.0f);
	Vector3 ay = *this * Vector3(0.0f, 1.0f, 0.0f);
	Vector3 az = *this * Vector3(0.0f, 0.0f, 1.0f);
	Vector3 result = Vector3(0.0f, 0.0f, 0.0f);

	if (az.y < 1.0f) {
		if (az.y > -1.0f) {
			result.x = std::asin(-az.y);
			result.y = std::atan2(az.x, az.z);
			result.z = std::atan2(ax.y, ay.y);
		}
		else {
			// Not a unique solution.
			result.x = Mathf::pi() / 2.0f;
			result.y = -std::atan2(-ay.x, ax.x);
			result.z = 0.0f;
		}
	}
	else {
		// Not a unique solution.
		result.x = -Mathf::pi() / 2.0f;
		result.y = std::atan2(-ay.x, ax.x);
		result.z = 0.0f;
	}
	return internal_make_positive(result * Mathf::rad_to_deg());
}

void Quaternion::euler_angles(const Vector3& value)
{
	*this = euler(value);
}

void Quaternion::set_from_to_rotation(const Vector3& fromDirection, const Vector3& toDirection)
{
	*this = from_to_rotation(fromDirection, toDirection);
}

void Quaternion::set_look_rotation(const Vector3& view, const Vector3& up)
{
	*this = look_rotation(view, up);
}

void Quaternion::to_angle_axis(float& angle, Vector3& axis)
{
	float a = std::acos(w);
	float s = std::sin(a);
	angle = a * 2.0f * Mathf::rad_to_deg();
	if (s > kEpsilon) {
		axis = Vector3{ x, y, z } *(1.0f / s);
	}
	else {
		axis = Vector3{ 1.0f, 0.0f, 0.0f };
		angle = 0.0f;
	}
}

Quaternion Quaternion::euler(float x, float y, float z)
{
	return euler(Vector3(x, y, z));
}

Quaternion Quaternion::euler(const Vector3& euler)
{
	Vector3 v = euler * Mathf::deg_to_rad();
	float c1 = std::cos(v.x * 0.5f);
	float c2 = std::cos(v.y * 0.5f);
	float c3 = std::cos(v.z * 0.5f);
	float s1 = std::sin(v.x * 0.5f);
	float s2 = std::sin(v.y * 0.5f);
	float s3 = std::sin(v.z * 0.5f);
	float x = s1 * c2 * c3 - c1 * s2 * s3;
	float y = c1 * s2 * c3 + s1 * c2 * s3;
	float z = c1 * c2 * s3 - s1 * s2 * c3;
	float w = c1 * c2 * c3 + s1 * s2 * s3;
	return Quaternion(x, y, z, w);
}

Quaternion Quaternion::from_to_rotation(const Vector3& fromDirection, const Vector3& toDirection)
{
	// 2ベクトル間の角度を求める
	float angle = Vector3::angle(fromDirection, toDirection);
	if (angle < kEpsilon) {
		return identity();
	}
	// 回転の軸を計算
	Vector3 axis = Vector3::cross(fromDirection, toDirection);
	// 回転の軸ができなかった場合の補正
	if (axis.sqr_magnitude() < (kEpsilon * kEpsilon)) {
		axis = Vector3::cross(Vector3{ 0.0f, 0.0f, 1.0f }, fromDirection);
		if (axis.sqr_magnitude() < (kEpsilon * kEpsilon)) {
			axis = Vector3::cross(Vector3{ 1.0f, 0.0f, 0.0f }, fromDirection);
		}
	}
	return angle_axis(angle, axis);
}

Quaternion Quaternion::look_rotation(const Vector3& view, const Vector3& up)
{
	// 前方のベクトルを求める
	Vector3 forward = Vector3::normalize(view);
	if (forward.sqr_magnitude() < (kEpsilon * kEpsilon)) {
		forward = Vector3{ 0.0f, 0.0f, 1.0f };
	}
	// 右手方向のベクトルを求める (OpenGLのような右手座標系では左手方向)
	Vector3 right = Vector3::cross(up, forward);
	if (right.sqr_magnitude() < (kEpsilon * kEpsilon)) {
		right = Vector3{ 1.0f, 0.0f, 0.0f };
	}
	// 上方向のベクトルを求める
	Vector3 upwards = Vector3::cross(forward, right);
	upwards.normalize();
	// 右手方向のベクトルを求める
	right = Vector3::cross(upwards, forward);
	Quaternion result;
	float radicand = right.x + upwards.y + forward.z;
	if (radicand > 0.0f) {
		result.w = std::sqrt(1.0f + radicand) * 0.5f;
		float recip = 1.0f / (4.0f * result.w);
		result.x = (upwards.z - forward.y) * recip;
		result.y = (forward.x - right.z) * recip;
		result.z = (right.y - upwards.x) * recip;
	}
	else if (right.x >= upwards.y && right.x >= forward.z) {
		result.x = std::sqrt(1.0f + right.x - upwards.y - forward.z) * 0.5f;
		float recip = 1.0f / (4.0f * result.x);
		result.w = (upwards.z - forward.y) * recip;
		result.z = (forward.x + right.z) * recip;
		result.y = (right.y + upwards.x) * recip;
	}
	else if (upwards.y > forward.z) {
		result.y = std::sqrt(1.0f - right.x + upwards.y - forward.z) * 0.5f;
		float recip = 1.0f / (4.0f * result.y);
		result.z = (upwards.z + forward.y) * recip;
		result.w = (forward.x - right.z) * recip;
		result.x = (right.y + upwards.x) * recip;
	}
	else {
		result.z = std::sqrt(1.0f - right.x - upwards.y + forward.z) * 0.5f;
		float recip = 1.0f / (4.0f * result.z);
		result.y = (upwards.z + forward.y) * recip;
		result.x = (forward.x + right.z) * recip;
		result.w = (right.y - upwards.x) * recip;
	}
	return result;
}

Quaternion Quaternion::rotate_towards(const Quaternion& from, const Quaternion& to, float maxDegreesDelta)
{
	float angle = Quaternion::angle(from, to);
	if (angle == 0.0f) return to;
	return slerp_unclamped(from, to, Mathf::min(1.0f, maxDegreesDelta / angle));
}

Quaternion Quaternion::lerp(const Quaternion& a, const Quaternion& b, float t)
{
	t = Mathf::clamp(t, 0.0f, 1.0f);
	return lerp_unclamped(a, b, t);
}

Quaternion Quaternion::lerp_unclamped(const Quaternion& a, const Quaternion& b, float t)
{
	float num = t;
	float num2 = 1.0f - num;
	Quaternion quaternion = Quaternion();
	float num5 = (((a.x * b.x) + (a.y * b.y)) + (a.z * b.z)) + (a.w * b.w);
	if (num5 >= 0.0f)
	{
		quaternion.x = (num2 * a.x) + (num * b.x);
		quaternion.y = (num2 * a.y) + (num * b.y);
		quaternion.z = (num2 * a.z) + (num * b.z);
		quaternion.w = (num2 * a.w) + (num * b.w);
	}
	else
	{
		quaternion.x = (num2 * a.x) - (num * b.x);
		quaternion.y = (num2 * a.y) - (num * b.y);
		quaternion.z = (num2 * a.z) - (num * b.z);
		quaternion.w = (num2 * a.w) - (num * b.w);
	}
	float num4 = (((quaternion.x * quaternion.x) + (quaternion.y * quaternion.y)) + (quaternion.z * quaternion.z)) + (quaternion.w * quaternion.w);
	float num3 = 1.0f / ((float)std::sqrt((double)num4));
	quaternion.x *= num3;
	quaternion.y *= num3;
	quaternion.z *= num3;
	quaternion.w *= num3;
	return quaternion;
}

bool Quaternion::equals(const Quaternion& other) const
{
	return this->x == other.x &&
		this->y == other.y &&
		this->z == other.z &&
		this->w == other.w;
}

bool Quaternion::is_equal_using_dot(float dot)
{
	return dot > 1.0f - kEpsilon;
}

EvaEngine::Quaternion::operator DirectX::XMVECTOR() const {
	return DirectX::XMLoadFloat4(&vec);
}

Quaternion EvaEngine::operator-(const Quaternion& q)
{
	return Quaternion(-q.x, -q.y, -q.z, -q.w);
}

Quaternion EvaEngine::operator+(const Quaternion& lhs, const Quaternion& rhs)
{
	return Quaternion(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
}

Quaternion EvaEngine::operator-(const Quaternion& lhs, const Quaternion& rhs)
{
	return Quaternion(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
}

Quaternion EvaEngine::operator*(const Quaternion& lhs, float rhs)
{
	return Quaternion(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs);
}

Quaternion EvaEngine::operator*(float lhs, const Quaternion& rhs)
{
	return Quaternion(rhs.x * lhs, rhs.y * lhs, rhs.z * lhs, rhs.w * lhs);
}

Quaternion EvaEngine::operator*(const Quaternion& lhs, const Quaternion& rhs)
{
	return Quaternion(
		lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y,
		lhs.w * rhs.y + lhs.y * rhs.w + lhs.z * rhs.x - lhs.x * rhs.z,
		lhs.w * rhs.z + lhs.z * rhs.w + lhs.x * rhs.y - lhs.y * rhs.x,
		lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z);
}

Quaternion EvaEngine::operator/(Quaternion lhs, float s)
{
	return lhs * (1.0f / s);
}

Vector3 EvaEngine::operator*(const Quaternion& rotation, const Vector3& point)
{
	float num = rotation.x * 2.0f;
	float num2 = rotation.y * 2.0f;
	float num3 = rotation.z * 2.0f;
	float num4 = rotation.x * num;
	float num5 = rotation.y * num2;
	float num6 = rotation.z * num3;
	float num7 = rotation.x * num2;
	float num8 = rotation.x * num3;
	float num9 = rotation.y * num3;
	float num10 = rotation.w * num;
	float num11 = rotation.w * num2;
	float num12 = rotation.w * num3;
	Vector3 result;
	result.x = (1.0f - (num5 + num6)) * point.x + (num7 - num12) * point.y + (num8 + num11) * point.z;
	result.y = (num7 + num12) * point.x + (1.0f - (num4 + num6)) * point.y + (num9 - num10) * point.z;
	result.z = (num8 - num11) * point.x + (num9 + num10) * point.y + (1.0f - (num4 + num5)) * point.z;
	return result;
}

bool EvaEngine::operator==(const Quaternion& lhs, const Quaternion& rhs)
{
	return lhs.equals(rhs);
}

bool EvaEngine::operator!=(const Quaternion& lhs, const Quaternion& rhs)
{
	return !lhs.equals(rhs);
}
