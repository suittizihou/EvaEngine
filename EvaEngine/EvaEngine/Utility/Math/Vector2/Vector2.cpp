#include "Vector2.h"
#include "../Vector3/Vector3.h"
#include "../Vector4/Vector4.h"
#include "../Color/Color.h"
#include "..//Mathf/Mathf.h"
#include <iostream>
#include <algorithm>

const float kEpsilon = 0.00001F;
const float kEpsilonNormalSqrt = 1e-15f;

using namespace EvaEngine;

Vector2::Vector2(float x, float y)
	:x{ x }, y{ y }
{
}

Vector2 Vector2::zero()
{
	return Vector2(0.0f, 0.0f);
}

Vector2 Vector2::one()
{
	return Vector2(1.0f, 1.0f);
}

Vector2 Vector2::up()
{
	return Vector2(0.0f, 1.0f);
}

Vector2 Vector2::down()
{
	return Vector2(0.0f, -1.0f);
}

Vector2 Vector2::left()
{
	return Vector2(-1.0f, 0.0f);
}

Vector2 Vector2::right()
{
	return Vector2(1.0f, 0.0f);
}

float Vector2::magnitude() const
{
	return std::sqrt(x * x + y * y);
}

Vector2 Vector2::normalized() const
{
	Vector2 v = Vector2(x, y);
	v.normalize();
	return v;
}

float Vector2::sqr_magnitude() const
{
	return x * x + y * y;
}

float Vector2::operator[](int index) const
{
	switch (index) {
	case 0: return x;
	case 1: return y;
	default:
		throw "配列の境界外";
	}
}

float& Vector2::operator[](int index)
{
	switch (index) {
	case 0: return x;
	case 1: return y;
	default:
		throw "配列の境界外";
	}
}

bool Vector2::equals(const Vector2& other)
{
	return x == other.x && y == other.y;
}

void Vector2::normalize()
{
	float mag = magnitude();
	if (mag > kEpsilon) {
		x = x / mag;
		y = y / mag;
	}
	else {
		x = 0.0f;
		y = 0.0f;
	}
}

void Vector2::set(float x, float y)
{
	this->x = x;
	this->y = y;
}

std::string Vector2::to_string() const
{
	return "x : " + std::to_string(x) + ", " + "y : " + std::to_string(y);
}

float Vector2::angle(const Vector2& from, const Vector2& to)
{
	float denominator = std::sqrt(from.sqr_magnitude() * to.sqr_magnitude());
	if (denominator < kEpsilonNormalSqrt)
		return 0.0f;

	float dot = Mathf::clamp(Vector2::dot(from, to) / denominator, -1.0f, 1.0f);
	return (float)std::acos(dot) * Mathf::rad_to_deg();
}

Vector2 Vector2::clamp_magnitude(const Vector2& vector, float max_length)
{
	float sqrtMagnitude = vector.sqr_magnitude();
	if (sqrtMagnitude > max_length * max_length) {
		float mag = (float)std::sqrt(sqrtMagnitude);
		
		float normalized_x = vector.x / mag;
		float normalized_y = vector.y / mag;
		return Vector2(normalized_x * max_length,
					   normalized_y * max_length);
	}
	return vector;
}

float Vector2::distance(const Vector2& a, const Vector2& b)
{
	float diff_x = a.x - b.x;
	float diff_y = a.y - b.y;
	return (float)std::sqrt(diff_x * diff_x + diff_y * diff_y);
}

float Vector2::dot(const Vector2& lhs, const Vector2& rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

Vector2 Vector2::lerp(const Vector2& a, const Vector2& b, float t)
{
	t = Mathf::clamp01(t);
	return Vector2(
		a.x + (b.x - a.x) * t,
		a.y + (b.y - a.y) * t
	);
}

Vector2 Vector2::lerp_unclamped(const Vector2& a, const Vector2& b, float t)
{
	return Vector2(
		a.x + (b.x - a.x) * t,
		a.y + (b.y - a.y) * t
	);
}

Vector2 Vector2::max(const Vector2& lhs, const Vector2& rhs)
{
	return Vector2(std::max(lhs.x, rhs.x),
				   std::max(lhs.y, rhs.y));
}

Vector2 Vector2::min(const Vector2& lhs, const Vector2& rhs)
{
	return Vector2(std::min(lhs.x, rhs.x),
				   std::min(lhs.y, rhs.y));
}

Vector2 Vector2::move_towards(const Vector2& current, const Vector2& target, float max_distance_delta)
{
	float toVector_x = target.x - current.x;
	float toVector_y = target.y - current.y;

	float sqDist = toVector_x * toVector_x + toVector_y * toVector_y;

	if (sqDist == 0 || (max_distance_delta >= 0 && sqDist <= max_distance_delta * max_distance_delta))
		return target;

	float dist = (float)std::sqrt(sqDist);

	return Vector2(current.x + toVector_x / dist * max_distance_delta,
				   current.y + toVector_y / dist * max_distance_delta);
}

Vector2 Vector2::perpendicular(Vector2 inDirection)
{
	return Vector2(-inDirection.y, inDirection.x);
}

Vector2 Vector2::reflect(const Vector2& inDirection, const Vector2& inNormal)
{
	float factor = -2.0f * dot(inNormal, inDirection);
	return Vector2(factor * inNormal.x + inDirection.x, factor * inNormal.y + inDirection.y);
}

Vector2 Vector2::scale(const Vector2& a, const Vector2& b)
{
	return Vector2(a.x * b.x, a.y * b.y);
}

float Vector2::signed_angle(const Vector2& from, const Vector2& to)
{
	float unsigned_angle = angle(from, to);
	float sign = Mathf::sign(from.x * to.y - from.y * to.x);
	return unsigned_angle * sign;
}

Vector2 Vector2::smooth_damp(const Vector2& current, const Vector2& target, Vector2& currentVelocity, float smooth_time, float max_speed, float delta_time)
{
	smooth_time = std::max(0.0001f, smooth_time);
	float omega = 2.0f / smooth_time;

	float x = omega * delta_time;
	float exp = 1.0f / (1.0f + x + 0.48f * x * x + 0.235f * x * x * x);

	float change_x = current.x - target.x;
	float change_y = current.y - target.y;
	Vector2 originalTo = target;

	float maxChange = max_speed * smooth_time;

	float maxChangeSq = maxChange * maxChange;
	float sqDist = change_x * change_x + change_y * change_y;
	if (sqDist > maxChangeSq) {
		auto mag = (float)std::sqrt(sqDist);
		change_x = change_x / mag * maxChange;
		change_y = change_y / mag * maxChange;
	}

	float temp_target_x = current.x - change_x;
	float temp_target_y = current.y - change_y;

	float temp_x = (currentVelocity.x + omega * change_x) * delta_time;
	float temp_y = (currentVelocity.y + omega * change_y) * delta_time;

	currentVelocity.x = (currentVelocity.x - omega * temp_x) * exp;
	currentVelocity.y = (currentVelocity.y - omega * temp_y) * exp;

	float output_x = temp_target_x + (change_x + temp_x) * exp;
	float output_y = temp_target_y + (change_y + temp_y) * exp;

	float origMinusCurrent_x = originalTo.x - current.x;
	float origMinusCurrent_y = originalTo.y - current.y;
	float outMinusOrig_x = output_x - originalTo.x;
	float outMinusOrig_y = output_y - originalTo.y;

	if (origMinusCurrent_x * outMinusOrig_x + origMinusCurrent_y * outMinusOrig_y > 0) {
		output_x = originalTo.x;
		output_y = originalTo.y;

		currentVelocity.x = (output_x - originalTo.x) / delta_time;
		currentVelocity.y = (output_y - originalTo.y) / delta_time;
	}
	return Vector2(output_x, output_y);
}

EvaEngine::Vector2::operator Vector3() const
{
	return Vector3(x, y, 0.0f);
}

EvaEngine::Vector2::operator Vector4() const
{
	return Vector4(x, y, 0.0f, 0.0f);
}

EvaEngine::Vector2::operator Color() const
{
	return Color(x, y, 0.0f, 0.0f);
}

EvaEngine::Vector2::operator DirectX::XMVECTOR() const {
	return DirectX::XMLoadFloat2(&vec);
}

Vector2 EvaEngine::operator-(const Vector2& v)
{
	return Vector2(-v.x, -v.y);
}

Vector2& EvaEngine::operator+=(Vector2& lhs, const Vector2& rhs)
{
	lhs.x += rhs.y;
	lhs.y += rhs.y;
	return lhs;
}

Vector2& EvaEngine::operator-=(Vector2& lhs, const Vector2& rhs)
{
	lhs.x -= rhs.y;
	lhs.y -= rhs.y;
	return lhs;
}

Vector2& EvaEngine::operator*=(Vector2& lhs, float rhs)
{
	lhs.x *= rhs;
	lhs.y *= rhs;
	return lhs;
}

Vector2& EvaEngine::operator/=(Vector2& lhs, float rhs)
{
	lhs.x /= rhs;
	lhs.y /= rhs;
	return lhs;
}

Vector2 EvaEngine::operator+(const Vector2& lhs, const Vector2& rhs)
{
	return Vector2(lhs.x + rhs.x, lhs.y + rhs.y);
}

Vector2 EvaEngine::operator-(const Vector2& lhs, const Vector2& rhs)
{
	return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
}

Vector2 EvaEngine::operator*(const Vector2& lhs, float rhs)
{
	return Vector2(lhs.x * rhs, lhs.y * rhs);
}

Vector2 EvaEngine::operator*(float lhs, const Vector2& rhs)
{
	return Vector2(lhs * rhs.x, lhs * rhs.y);
}

Vector2 EvaEngine::operator/(const Vector2& lhs, float rhs)
{
	return Vector2(lhs.x / rhs, lhs.y / rhs);
}

bool EvaEngine::operator==(const Vector2& lhs, const Vector2& rhs)
{
	float diff_x = lhs.x - rhs.x;
	float diff_y = lhs.y - rhs.y;
	return (diff_x * diff_x + diff_y * diff_y) < kEpsilon * kEpsilon;
}

bool EvaEngine::operator!=(const Vector2& lhs, const Vector2& rhs)
{
	return !(lhs == rhs);
}
