#include "Vector2Int.h"
#include "../Vector3Int/Vector3Int.h"
#include "..//Mathf/Mathf.h"
#include <iostream>
#include <algorithm>

const int kEpsilon = 0.00001F;
const int kEpsilonNormalSqrt = 1e-15f;

using namespace EvaEngine;

Vector2Int::Vector2Int(int x, int y)
	:x{ x }, y{ y }
{
}

Vector2Int Vector2Int::zero()
{
	return Vector2Int(0, 0);
}

Vector2Int Vector2Int::one()
{
	return Vector2Int(1, 1);
}

Vector2Int Vector2Int::up()
{
	return Vector2Int(0, 1);
}

Vector2Int Vector2Int::down()
{
	return Vector2Int(0, -1);
}

Vector2Int Vector2Int::left()
{
	return Vector2Int(-1, 0);
}

Vector2Int Vector2Int::right()
{
	return Vector2Int(1, 0);
}

int Vector2Int::magnitude() const
{
	return std::sqrt(x * x + y * y);
}

int Vector2Int::sqr_magnitude() const
{
	return x * x + y * y;
}

int Vector2Int::operator[](int index) const
{
	switch (index) {
	case 0: return x;
	case 1: return y;
	default:
		throw "”z—ñ‚Ì‹«ŠEŠO";
	}
}

int& Vector2Int::operator[](int index)
{
	switch (index) {
	case 0: return x;
	case 1: return y;
	default:
		throw "”z—ñ‚Ì‹«ŠEŠO";
	}
}

bool Vector2Int::equals(const Vector2Int& other)
{
	return x == other.x && y == other.y;
}

void Vector2Int::set(int x, int y)
{
	this->x = x;
	this->y = y;
}

std::string Vector2Int::to_string() const
{
	return "x : " + std::to_string(x) + ", " + "y : " + std::to_string(y);
}

Vector2Int Vector2Int::clamp_magnitude(const Vector2Int& vector, int max_length)
{
	int sqrtMagnitude = vector.sqr_magnitude();
	if (sqrtMagnitude > max_length * max_length) {
		int mag = (int)std::sqrt(sqrtMagnitude);

		int normalized_x = vector.x / mag;
		int normalized_y = vector.y / mag;
		return Vector2Int(normalized_x * max_length,
			normalized_y * max_length);
	}
	return vector;
}

int Vector2Int::distance(const Vector2Int& a, const Vector2Int& b)
{
	int diff_x = a.x - b.x;
	int diff_y = a.y - b.y;
	return (int)std::sqrt(diff_x * diff_x + diff_y * diff_y);
}

int Vector2Int::dot(const Vector2Int& lhs, const Vector2Int& rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

Vector2Int Vector2Int::max(const Vector2Int& lhs, const Vector2Int& rhs)
{
	return Vector2Int(std::max(lhs.x, rhs.x),
		std::max(lhs.y, rhs.y));
}

Vector2Int Vector2Int::min(const Vector2Int& lhs, const Vector2Int& rhs)
{
	return Vector2Int(std::min(lhs.x, rhs.x),
		std::min(lhs.y, rhs.y));
}

Vector2Int Vector2Int::scale(const Vector2Int& a, const Vector2Int& b)
{
	return Vector2Int(a.x * b.x, a.y * b.y);
}

EvaEngine::Vector2Int::operator Vector3Int() const
{
	return Vector3Int(x, y, 0);
}

EvaEngine::Vector2Int::operator DirectX::XMVECTOR() const {
	return DirectX::XMVectorSetInt(vec.x, vec.y, 0, 0);
}

Vector2Int EvaEngine::operator-(const Vector2Int& v)
{
	return Vector2Int(-v.x, -v.y);
}

Vector2Int& EvaEngine::operator+=(Vector2Int& lhs, const Vector2Int& rhs)
{
	lhs.x += rhs.y;
	lhs.y += rhs.y;
	return lhs;
}

Vector2Int& EvaEngine::operator-=(Vector2Int& lhs, const Vector2Int& rhs)
{
	lhs.x -= rhs.y;
	lhs.y -= rhs.y;
	return lhs;
}

Vector2Int& EvaEngine::operator*=(Vector2Int& lhs, int rhs)
{
	lhs.x *= rhs;
	lhs.y *= rhs;
	return lhs;
}

Vector2Int& EvaEngine::operator/=(Vector2Int& lhs, int rhs)
{
	lhs.x /= rhs;
	lhs.y /= rhs;
	return lhs;
}

Vector2Int EvaEngine::operator+(const Vector2Int& lhs, const Vector2Int& rhs)
{
	return Vector2Int(lhs.x + rhs.x, lhs.y + rhs.y);
}

Vector2Int EvaEngine::operator-(const Vector2Int& lhs, const Vector2Int& rhs)
{
	return Vector2Int(lhs.x - rhs.x, lhs.y - rhs.y);
}

Vector2Int EvaEngine::operator*(const Vector2Int& lhs, int rhs)
{
	return Vector2Int(lhs.x * rhs, lhs.y * rhs);
}

Vector2Int EvaEngine::operator*(int lhs, const Vector2Int& rhs)
{
	return Vector2Int(lhs * rhs.x, lhs * rhs.y);
}

Vector2Int EvaEngine::operator/(const Vector2Int& lhs, int rhs)
{
	return Vector2Int(lhs.x / rhs, lhs.y / rhs);
}

bool EvaEngine::operator==(const Vector2Int& lhs, const Vector2Int& rhs)
{
	int diff_x = lhs.x - rhs.x;
	int diff_y = lhs.y - rhs.y;
	return (diff_x * diff_x + diff_y * diff_y) < kEpsilon * kEpsilon;
}

bool EvaEngine::operator!=(const Vector2Int& lhs, const Vector2Int& rhs)
{
	return !(lhs == rhs);
}
