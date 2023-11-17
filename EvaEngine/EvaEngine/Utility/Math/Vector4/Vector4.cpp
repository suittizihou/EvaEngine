#include "Vector4.h"
#include "../Vector2/Vector2.h"
#include "../Vector3/Vector3.h"
#include "../Color/Color.h"
#include "..//Mathf/Mathf.h"
#include <stdexcept>
#include <algorithm>

using namespace EvaEngine;

const float Vector4::kEpsilon{ 0.00001F };
const float kEpsilonNormalSqrt = 1e-15f;

Vector4::Vector4(float x, float y, float z, float w)
	: x{ x }, y{ y }, z{ z }, w{ w }
{
}

float Vector4::magnitude() const
{
	return std::sqrt(x * x + y * y + z * z);
}

Vector4 Vector4::normalized() const
{
	Vector4 v = Vector4(x, y, z, w);
	v.normalize();
	return v;
}

float Vector4::sqr_magnitude() const
{
	return x * x + y * y + z * z + w * w;
}

float Vector4::operator[](int index) const
{
	switch (index) {
	case 0: return x;
	case 1: return y;
	case 2: return z;
	case 3: return w;
	default:
		throw std::range_error("配列の境界外");
	}
}

float& Vector4::operator[](int index)
{
	switch (index) {
	case 0: return x;
	case 1: return y;
	case 2:	return z;
	case 3:	return w;
	default:
		throw std::range_error("配列の境界外");
	}
}

bool Vector4::equals(const Vector4& other) const
{
	return x == other.x && y == other.y && z == other.z && w == other.w;
}

void Vector4::normalize()
{
	float mag = magnitude();
	if (mag > kEpsilon) {
		x = x / mag;
		y = y / mag;
		z = z / mag;
		w = w / mag;
	}
	else {
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 0.0f;
	}
}

void Vector4::scale(const Vector4& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	w *= v.w;
}

void Vector4::set(float new_x, float new_y, float new_z, float new_w)
{
	x = new_x;
	y = new_y;
	z = new_z;
	w = new_w;
}

std::string Vector4::to_string() const
{
	return "x : " + std::to_string(x) + ", y : " + std::to_string(y) + ", z : " + std::to_string(z) + ", w : " + std::to_string(w);
}

float Vector4::angle(const Vector4& from, const Vector4& to)
{
	float denominator = (float)std::sqrt(from.sqr_magnitude() * to.sqr_magnitude());
	if (denominator < kEpsilonNormalSqrt)
		return 0;

	float dot = Mathf::clamp(Vector4::dot(from, to) / denominator, -1, 1);
	return ((float)std::acos(dot)) * Mathf::rad_to_deg();
}

Vector4 Vector4::clamp_magnitude(const Vector4& vector, float max_length)
{
	float sqrmag = vector.sqr_magnitude();
	if (sqrmag > max_length * max_length) {
		float mag = (float)std::sqrt(sqrmag);
		float normalized_x = vector.x / mag;
		float normalized_y = vector.y / mag;
		float normalized_z = vector.z / mag;
		float normalized_w = vector.w / mag;
		return Vector4(
			normalized_x * max_length,
			normalized_y * max_length,
			normalized_z * max_length,
			normalized_w * max_length);
	}
	return vector;
}

float Vector4::distance(const Vector4& a, const Vector4 b)
{
	float diff_x = a.x - b.x;
	float diff_y = a.y - b.y;
	float diff_z = a.z - b.z;
	float diff_w = a.w - b.w;
	return (float)std::sqrt(diff_x * diff_x + diff_y * diff_y + diff_z * diff_z + diff_w * diff_w);
}

Vector4 EvaEngine::operator-(const Vector4& v)
{
	return Vector4(-v.x, -v.y, -v.z, -v.w);
}

Vector4& EvaEngine::operator+=(Vector4& lhs, const Vector4& rhs)
{
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	lhs.z += rhs.z;
	lhs.w += rhs.w;
	return lhs;
}

Vector4& EvaEngine::operator-=(Vector4& lhs, const Vector4& rhs)
{
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
	lhs.z -= rhs.z;
	lhs.w -= rhs.w;
	return lhs;
}

Vector4& EvaEngine::operator*=(Vector4& lhs, float rhs)
{
	lhs.x *= rhs;
	lhs.y *= rhs;
	lhs.z *= rhs;
	lhs.w *= rhs;
	return lhs;
}

Vector4& EvaEngine::operator/=(Vector4& lhs, float rhs)
{
	lhs.x /= rhs;
	lhs.y /= rhs;
	lhs.z /= rhs;
	lhs.w /= rhs;
	return lhs;
}

Vector4 EvaEngine::operator+(const Vector4& lhs, const Vector4& rhs)
{
	return Vector4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
}

Vector4 EvaEngine::operator-(const Vector4& lhs, const Vector4& rhs)
{
	return Vector4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
}

Vector4 EvaEngine::operator*(const Vector4& lhs, float rhs)
{
	return Vector4(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs);
}

Vector4 EvaEngine::operator*(float lhs, const Vector4& rhs)
{
	return Vector4(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w);
}

Vector4 EvaEngine::operator/(const Vector4& lhs, float rhs)
{
	return Vector4(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs, lhs.w / rhs);
}

bool EvaEngine::operator==(const Vector4& lhs, const Vector4& rhs)
{
	float diff_x = lhs.x - rhs.x;
	float diff_y = lhs.y - rhs.y;
	float diff_z = lhs.z - rhs.z;
	float diff_w = lhs.w - rhs.w;
	float sqrmag = diff_x * diff_x + diff_y * diff_y + diff_z * diff_z + diff_w * diff_w;
	return sqrmag < Vector4::kEpsilon * Vector4::kEpsilon;
}

bool EvaEngine::operator!=(const Vector4& lhs, const Vector4& rhs)
{
	return !(lhs == rhs);
}

float Vector4::dot(const Vector4& lhs, const Vector4& rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}

Vector4 Vector4::lerp(const Vector4& a, const Vector4& b, float t)
{
	t = Mathf::clamp01(t);
	return Vector4(
		a.x + (b.x - a.x) * t,
		a.y + (b.y - a.y) * t,
		a.z + (b.z - a.z) * t,
		a.w + (b.w - a.w) * t
	);
}

Vector4 Vector4::lerp_unclamped(const Vector4& a, const Vector4& b, float t)
{
	return Vector4(
		a.x + (b.x - a.x) * t,
		a.y + (b.y - a.y) * t,
		a.z + (b.z - a.z) * t,
		a.w + (b.w - a.w) * t);
}

Vector4 Vector4::max(const Vector4& lhs, const Vector4& rhs)
{
	return Vector4(std::max(lhs.x, rhs.x), std::max(lhs.y, rhs.y), std::max(lhs.z, rhs.z), std::max(lhs.w, rhs.w));
}

Vector4 Vector4::min(const Vector4& lhs, const Vector4& rhs)
{
	return Vector4(std::min(lhs.x, rhs.x), std::min(lhs.y, rhs.y), std::min(lhs.z, rhs.z), std::min(lhs.w, rhs.w));
}

Vector4 Vector4::move_towards(const Vector4& current, const Vector4& target, float max_distance_delta)
{
	float toVector_x = target.x - current.x;
	float toVector_y = target.y - current.y;
	float toVector_z = target.z - current.z;
	float toVector_w = target.w - current.w;

	float sqdist = toVector_x * toVector_x + toVector_y * toVector_y + toVector_z * toVector_z + toVector_w * toVector_w;

	if (sqdist == 0 || sqdist <= max_distance_delta * max_distance_delta)
		return target;
	auto dist = (float)std::sqrt(sqdist);

	return Vector4(
		current.x + toVector_x / dist * max_distance_delta,
		current.y + toVector_y / dist * max_distance_delta,
		current.z + toVector_z / dist * max_distance_delta,
		current.w + toVector_w / dist * max_distance_delta);
}

Vector4 Vector4::normalize(const Vector4& value)
{
	float mag = value.magnitude();
	if (mag > kEpsilon) return value / mag;
	else return zero();
}

Vector4 Vector4::project(const Vector4& vector, const Vector4& onNormal)
{
	float sqrMag = dot(onNormal, onNormal);
	if (sqrMag < kEpsilon) {
		return zero();
	}
	else {
		auto dot = Vector4::dot(vector, onNormal);
		return Vector4(
			onNormal.x * dot / sqrMag,
			onNormal.y * dot / sqrMag,
			onNormal.z * dot / sqrMag,
			onNormal.w * dot / sqrMag);
	}
}

Vector4 Vector4::project_on_plane(const Vector4& vector, const Vector4& planeNormal)
{
	float sqrMag = dot(planeNormal, planeNormal);
	if (sqrMag < kEpsilon)
		return vector;
	else
	{
		auto dot = Vector4::dot(vector, planeNormal);
		return Vector4(
			vector.x - planeNormal.x * dot / sqrMag,
			vector.y - planeNormal.y * dot / sqrMag,
			vector.z - planeNormal.z * dot / sqrMag,
			vector.w - planeNormal.w * dot / sqrMag);
	}
}

Vector4 Vector4::reflect(const Vector4& inDirection, const Vector4& inNormal)
{
	float factor = -2.0f * dot(inNormal, inDirection);
	return Vector4(
		factor * inNormal.x + inDirection.x,
		factor * inNormal.y + inDirection.y,
		factor * inNormal.z + inDirection.z,
		factor * inNormal.w + inDirection.w);
}

Vector4 Vector4::scale(const Vector4& a, const Vector4& b)
{
	return Vector4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

EvaEngine::Vector4::operator Color() const { return Color(x, y, z, w); }

EvaEngine::Vector4::operator Vector2() const { return Vector2(x, y); }

EvaEngine::Vector4::operator Vector3() const { return Vector3(x, y, z); }

EvaEngine::Vector4::operator DirectX::XMVECTOR() const { return DirectX::XMLoadFloat4(&vec); }