#include "Vector3Int.h"
#include "../Vector2Int/Vector2Int.h"
#include "..//Mathf/Mathf.h"
#include <stdexcept>
#include <algorithm>

using namespace EvaEngine;

Vector3Int::Vector3Int(int x, int y, int z)
	: x{ x }, y{ y }, z{ z }
{
}

int Vector3Int::magnitude() const
{
	return std::sqrt(x * x + y * y + z * z);
}

int Vector3Int::sqr_magnitude() const
{
	return x * x + y * y + z * z;
}

int Vector3Int::operator[](int index) const
{
	switch (index) {
	case 0: return x;
	case 1: return y;
	case 2: return z;
	default:
		throw std::range_error("”z—ñ‚Ì‹«ŠEŠO");
	}
}

int& Vector3Int::operator[](int index)
{
	switch (index) {
	case 0: return x;
	case 1: return y;
	case 2:	return z;
	default:
		throw std::range_error("”z—ñ‚Ì‹«ŠEŠO");
	}
}

bool Vector3Int::equals(const Vector3Int& other) const
{
	return x == other.x && y == other.y && z == other.z;
}

void Vector3Int::scale(const Vector3Int& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
}

void Vector3Int::set(int new_x, int new_y, int new_z)
{
	x = new_x;
	y = new_y;
	z = new_z;
}

std::string Vector3Int::to_string() const
{
	return "x : " + std::to_string(x) + ", y : " + std::to_string(y) + ", z : " + std::to_string(z);
}

Vector3Int Vector3Int::clamp_magnitude(const Vector3Int& vector, int max_length)
{
	int sqrmag = vector.sqr_magnitude();
	if (sqrmag > max_length * max_length) {
		int mag = (int)std::sqrt(sqrmag);
		int normalized_x = vector.x / mag;
		int normalized_y = vector.y / mag;
		int normalized_z = vector.z / mag;
		return Vector3Int(normalized_x * max_length,
			normalized_y * max_length,
			normalized_z * max_length);
	}
	return vector;
}

Vector3Int Vector3Int::cross(const Vector3Int& lhs, const Vector3Int& rhs)
{
	return Vector3Int(lhs.y * rhs.z - lhs.z * rhs.y,
		lhs.z * rhs.x - lhs.x * rhs.z,
		lhs.x * rhs.y - lhs.y * rhs.x);;
}

int Vector3Int::distance(const Vector3Int& a, const Vector3Int b)
{
	int diff_x = a.x - b.x;
	int diff_y = a.y - b.y;
	int diff_z = a.z - b.z;
	return (int)std::sqrt(diff_x * diff_x + diff_y * diff_y + diff_z * diff_z);
}

Vector3Int EvaEngine::operator-(const Vector3Int& v)
{
	return Vector3Int(-v.x, -v.y, -v.z);
}

Vector3Int& EvaEngine::operator+=(Vector3Int& lhs, const Vector3Int& rhs)
{
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	lhs.z += rhs.z;
	return lhs;
}

Vector3Int& EvaEngine::operator-=(Vector3Int& lhs, const Vector3Int& rhs)
{
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
	lhs.z -= rhs.z;
	return lhs;
}

Vector3Int& EvaEngine::operator*=(Vector3Int& lhs, int rhs)
{
	lhs.x *= rhs;
	lhs.y *= rhs;
	lhs.z *= rhs;
	return lhs;
}

Vector3Int& EvaEngine::operator/=(Vector3Int& lhs, int rhs)
{
	if (rhs == 0) {
		lhs = Vector3Int::zero();
	}
	else {
		lhs.x /= rhs;
		lhs.y /= rhs;
		lhs.z /= rhs;
	}
	return lhs;
}

Vector3Int EvaEngine::operator+(const Vector3Int& lhs, const Vector3Int& rhs)
{
	return Vector3Int(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

Vector3Int EvaEngine::operator-(const Vector3Int& lhs, const Vector3Int& rhs)
{
	return Vector3Int(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

Vector3Int EvaEngine::operator*(const Vector3Int& lhs, int rhs)
{
	return Vector3Int(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs);
}

Vector3Int EvaEngine::operator*(int lhs, const Vector3Int& rhs)
{
	return Vector3Int(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z);
}

Vector3Int EvaEngine::operator/(const Vector3Int& lhs, int rhs)
{
	return Vector3Int(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs);
}

bool EvaEngine::operator==(const Vector3Int& lhs, const Vector3Int& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

bool EvaEngine::operator!=(const Vector3Int& lhs, const Vector3Int& rhs)
{
	return !(lhs == rhs);
}

int Vector3Int::dot(const Vector3Int& lhs, const Vector3Int& rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

Vector3Int Vector3Int::max(const Vector3Int& lhs, const Vector3Int& rhs)
{
	return Vector3Int(std::max(lhs.x, rhs.x), std::max(lhs.y, rhs.y), std::max(lhs.z, rhs.z));
}

Vector3Int Vector3Int::min(const Vector3Int& lhs, const Vector3Int& rhs)
{
	return Vector3Int(std::min(lhs.x, rhs.x), std::min(lhs.y, rhs.y), std::min(lhs.z, rhs.z));
}

Vector3Int Vector3Int::scale(const Vector3Int& a, const Vector3Int& b)
{
	return Vector3Int(a.x * b.x, a.y * b.y, a.z * b.z);
}

EvaEngine::Vector3Int::operator Vector2Int() const
{
	return Vector2Int(x, y);
}

EvaEngine::Vector3Int::operator DirectX::XMVECTOR() const
{
	return DirectX::XMVectorSetInt(vec.x, vec.y, vec.z, 0);
}
