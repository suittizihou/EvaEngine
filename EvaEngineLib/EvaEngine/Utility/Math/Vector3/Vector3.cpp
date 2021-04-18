#include "Vector3.h"
#include "..//Mathf/Mathf.h"
#include <stdexcept>
#include <algorithm>

using namespace EvaEngine;

const float Vector3::kEpsilon { 0.00001F };
const float kEpsilonNormalSqrt = 1e-15f;

Vector3::Vector3(float x, float y, float z)
	: x{ x }, y{ y }, z{ z }
{
}

float Vector3::magnitude() const
{
	return std::sqrt(x * x + y * y + z * z);
}

Vector3 Vector3::normalized() const
{
	Vector3 v = Vector3(x, y, z);
	v.normalize();
	return v;
}

float Vector3::sqr_magnitude() const
{
	return x * x + y * y + z * z;
}

float Vector3::operator[](int index) const
{
	switch (index) {
	case 0: return x;
	case 1: return y;
	case 2: return z;
	default:
		throw std::range_error("”z—ñ‚Ì‹«ŠEŠO");
	}
}

float& Vector3::operator[](int index)
{
	switch (index) {
	case 0: return x;
	case 1: return y;
	case 2:	return z;
	default:
		throw std::range_error("”z—ñ‚Ì‹«ŠEŠO");
	}
}

bool Vector3::equals(const Vector3& other) const
{
	return x == other.x && y == other.y && z == other.z;
}

void Vector3::normalize()
{
	float mag = magnitude();
	if (mag > kEpsilon) {
		x = x / mag;
		y = y / mag;
		z = z / mag;
	}
	else {
		x = 0;
		y = 0;
		z = 0;
	}
}

void Vector3::scale(const Vector3& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
}

void Vector3::set(float new_x, float new_y, float new_z)
{
	x = new_x;
	y = new_y;
	z = new_z;
}

std::string Vector3::to_string() const
{
	return "x : " + std::to_string(x) + ", y : " + std::to_string(y) + ", z : " + std::to_string(z);
}

float Vector3::angle(const Vector3& from, const Vector3& to)
{
	float denominator = (float)std::sqrt(from.sqr_magnitude() * to.sqr_magnitude());
	if (denominator < kEpsilonNormalSqrt)
		return 0;

	float dot = Mathf::clamp(Vector3::dot(from, to) / denominator, -1, 1);
	return ((float)std::acos(dot)) * Mathf::rad_to_deg();
}

Vector3 Vector3::clamp_magnitude(const Vector3& vector, float max_length)
{
	float sqrmag = vector.sqr_magnitude();
	if (sqrmag > max_length * max_length) {
		float mag = (float)std::sqrt(sqrmag);
		float normalized_x = vector.x / mag;
		float normalized_y = vector.y / mag;
		float normalized_z = vector.z / mag;
		return Vector3(normalized_x * max_length,
			normalized_y * max_length,
			normalized_z * max_length);
	}
	return vector;
}

Vector3 Vector3::cross(const Vector3& lhs, const Vector3& rhs)
{
	return Vector3(lhs.y * rhs.z - lhs.z * rhs.y,
				   lhs.z * rhs.x - lhs.x * rhs.z,
				   lhs.x * rhs.y - lhs.y * rhs.x);;
}

float Vector3::distance(const Vector3& a, const Vector3 b)
{
	float diff_x = a.x - b.x;
	float diff_y = a.y - b.y;
	float diff_z = a.z - b.z;
	return (float)std::sqrt(diff_x * diff_x + diff_y * diff_y + diff_z * diff_z);
}

Vector3 EvaEngine::operator-(const Vector3& v)
{
	return Vector3(-v.x, -v.y, -v.z);
}

Vector3& EvaEngine::operator+=(Vector3& lhs, const Vector3& rhs)
{
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	lhs.z += rhs.z;
	return lhs;
}

Vector3& EvaEngine::operator-=(Vector3& lhs, const Vector3& rhs)
{
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
	lhs.z -= rhs.z;
	return lhs;
}

Vector3& EvaEngine::operator*=(Vector3& lhs, float rhs)
{
	lhs.x *= rhs;
	lhs.y *= rhs;
	lhs.z *= rhs;
	return lhs;
}

Vector3& EvaEngine::operator/=(Vector3& lhs, float rhs)
{
	lhs.x /= rhs;
	lhs.y /= rhs;
	lhs.z /= rhs;
	return lhs;
}

Vector3 EvaEngine::operator+(const Vector3& lhs, const Vector3& rhs)
{
	return Vector3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

Vector3 EvaEngine::operator-(const Vector3& lhs, const Vector3& rhs)
{
	return Vector3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

Vector3 EvaEngine::operator*(const Vector3& lhs, float rhs)
{
	return Vector3(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
}

Vector3 EvaEngine::operator*(float lhs, const Vector3& rhs)
{
	return Vector3(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
}

Vector3 EvaEngine::operator/(const Vector3& lhs, float rhs)
{
	return Vector3(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
}

bool EvaEngine::operator==(const Vector3& lhs, const Vector3& rhs)
{
	float diff_x = lhs.x - rhs.x;
	float diff_y = lhs.y - rhs.y;
	float diff_z = lhs.z - rhs.z;
	float sqrmag = diff_x * diff_x + diff_y * diff_y + diff_z * diff_z;
	return sqrmag < Vector3::kEpsilon * Vector3::kEpsilon;
}

bool EvaEngine::operator!=(const Vector3& lhs, const Vector3& rhs)
{
	return !(lhs == rhs);
}

float Vector3::dot(const Vector3& lhs, const Vector3& rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

Vector3 Vector3::lerp(const Vector3& a, const Vector3& b, float t)
{
	t = Mathf::clamp01(t);
	return Vector3(
		a.x + (b.x - a.x) * t,
		a.y + (b.y - a.y) * t,
		a.z + (b.z - a.z) * t
	);
}

Vector3 Vector3::lerp_unclamped(const Vector3& a, const Vector3& b, float t)
{
	return Vector3(a.x + (b.x - a.x) * t,
				   a.y + (b.y - a.y) * t,
				   a.z + (b.z - a.z) * t);
}

Vector3 Vector3::max(const Vector3& lhs, const Vector3& rhs)
{
	return Vector3(std::max(lhs.x, rhs.x), std::max(lhs.y, rhs.y), std::max(lhs.z, rhs.z));
}

Vector3 Vector3::min(const Vector3& lhs, const Vector3& rhs)
{
	return Vector3(std::min(lhs.x, rhs.x), std::min(lhs.y, rhs.y), std::min(lhs.z, rhs.z));
}

Vector3 Vector3::move_towards(const Vector3& current, const Vector3& target, float max_distance_delta)
{
	float toVector_x = target.x - current.x;
	float toVector_y = target.y - current.y;
	float toVector_z = target.z - current.z;

	float sqdist = toVector_x * toVector_x + toVector_y * toVector_y + toVector_z * toVector_z;

	if (sqdist == 0 || sqdist <= max_distance_delta * max_distance_delta)
		return target;
	auto dist = (float)std::sqrt(sqdist);

	return Vector3(current.x + toVector_x / dist * max_distance_delta,
				   current.y + toVector_y / dist * max_distance_delta,
				   current.z + toVector_z / dist * max_distance_delta);
}

Vector3 Vector3::normalize(const Vector3& value)
{
	float mag = value.magnitude();
	if (mag > kEpsilon) return value / mag;
	else return zero();
}

Vector3 Vector3::project(const Vector3& vector, const Vector3& onNormal)
{
	float sqrMag = dot(onNormal, onNormal);
	if (sqrMag < kEpsilon) {
		return zero();
	}
	else {
		auto dot = Vector3::dot(vector, onNormal);
		return Vector3(onNormal.x * dot / sqrMag,
					   onNormal.y * dot / sqrMag,
					   onNormal.z * dot / sqrMag);
	}
}

Vector3 Vector3::project_on_plane(const Vector3& vector, const Vector3& planeNormal)
{
	float sqrMag = dot(planeNormal, planeNormal);
	if (sqrMag < kEpsilon)
		return vector;
	else
	{
		auto dot = Vector3::dot(vector, planeNormal);
		return Vector3(vector.x - planeNormal.x * dot / sqrMag,
					   vector.y - planeNormal.y * dot / sqrMag,
					   vector.z - planeNormal.z * dot / sqrMag);
	}
}

Vector3 Vector3::reflect(const Vector3& inDirection, const Vector3& inNormal)
{
	float factor = -2.0f * dot(inNormal, inDirection);
	return Vector3(factor * inNormal.x + inDirection.x,
				   factor * inNormal.y + inDirection.y,
				   factor * inNormal.z + inDirection.z);
}

Vector3 Vector3::scale(const Vector3& a, const Vector3& b)
{
	return Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
}

float Vector3::signed_angle(const Vector3& from, const Vector3& to, const Vector3& axis)
{
	float unsignedAngle = angle(from, to);

	float cross_x = from.y * to.z - from.z * to.y;
	float cross_y = from.z * to.x - from.x * to.z;
	float cross_z = from.x * to.y - from.y * to.x;
	float sign = Mathf::sign(axis.x * cross_x + axis.y * cross_y + axis.z * cross_z);
	return unsignedAngle * sign;
}

Vector3 Vector3::smooth_damp(const Vector3& current, const Vector3& target, Vector3& currentVelocity, float smoothTime, float maxSpeed, float deltaTime)
{
	float output_x = 0.0f;
	float output_y = 0.0f;
	float output_z = 0.0f;

	// Based on Game Programming Gems 4 Chapter 1.10
	smoothTime = std::max(0.0001f, smoothTime);
	float omega = 2.0f / smoothTime;

	float x = omega * deltaTime;
	float exp = 1.0f / (1.0f + x + 0.48F * x * x + 0.235F * x * x * x);

	float change_x = current.x - target.x;
	float change_y = current.y - target.y;
	float change_z = current.z - target.z;
	Vector3 originalTo = target;

	// Clamp maximum speed
	float maxChange = maxSpeed * smoothTime;

	float maxChangeSq = maxChange * maxChange;
	float sqrmag = change_x * change_x + change_y * change_y + change_z * change_z;
	if (sqrmag > maxChangeSq)
	{
		auto mag = (float)std::sqrt(sqrmag);
		change_x = change_x / mag * maxChange;
		change_y = change_y / mag * maxChange;
		change_z = change_z / mag * maxChange;
	}

	Vector3 target_temp{};

	target_temp.x = current.x - change_x;
	target_temp.y = current.y - change_y;
	target_temp.z = current.z - change_z;

	float temp_x = (currentVelocity.x + omega * change_x) * deltaTime;
	float temp_y = (currentVelocity.y + omega * change_y) * deltaTime;
	float temp_z = (currentVelocity.z + omega * change_z) * deltaTime;

	currentVelocity.x = (currentVelocity.x - omega * temp_x) * exp;
	currentVelocity.y = (currentVelocity.y - omega * temp_y) * exp;
	currentVelocity.z = (currentVelocity.z - omega * temp_z) * exp;

	output_x = target_temp.x + (change_x + temp_x) * exp;
	output_y = target_temp.y + (change_y + temp_y) * exp;
	output_z = target_temp.z + (change_z + temp_z) * exp;

	// Prevent overshooting
	float origMinusCurrent_x = originalTo.x - current.x;
	float origMinusCurrent_y = originalTo.y - current.y;
	float origMinusCurrent_z = originalTo.z - current.z;
	float outMinusOrig_x = output_x - originalTo.x;
	float outMinusOrig_y = output_y - originalTo.y;
	float outMinusOrig_z = output_z - originalTo.z;

	if (origMinusCurrent_x * outMinusOrig_x + origMinusCurrent_y * outMinusOrig_y + origMinusCurrent_z * outMinusOrig_z > 0)
	{
		output_x = originalTo.x;
		output_y = originalTo.y;
		output_z = originalTo.z;

		currentVelocity.x = (output_x - originalTo.x) / deltaTime;
		currentVelocity.y = (output_y - originalTo.y) / deltaTime;
		currentVelocity.z = (output_z - originalTo.z) / deltaTime;
	}

	return Vector3(output_x, output_y, output_z);
}