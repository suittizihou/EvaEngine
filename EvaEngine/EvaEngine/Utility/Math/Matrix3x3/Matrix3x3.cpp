#include "Matrix3x3.h"
#include "../Vector2/Vector2.h"
#include <iostream>
#include  <cmath>

using namespace EvaEngine;

Matrix3x3::Matrix3x3(float m11, float m12, float m13, float m21, float m22, float m23, float m31, float m32, float m33)
{
	m[0][0] = m11; m[0][1] = m12; m[0][2] = m13;
	m[1][0] = m21; m[1][1] = m22; m[1][2] = m23;
	m[2][0] = m31; m[2][1] = m32; m[2][2] = m33;
}

Matrix3x3 Matrix3x3::zero()
{
	return Matrix3x3(
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f);
}

Matrix3x3 Matrix3x3::identity()
{
	return Matrix3x3(
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f);
}

Matrix3x3 Matrix3x3::scale(const Vector2& vector)
{
	return Matrix3x3(
		vector.x, 0.0f, 0.0f,
		0.0f, vector.y, 0.0f,
		0.0f, 0.0f, 1.0f);
}

Matrix3x3 Matrix3x3::rotate(float rotation)
{
	float rad = rotation * (3.14159265359f / 180.0f);
	float cos = std::cos(rad);
	float sin = std::sin(rad);

	return Matrix3x3(
		cos, sin, 0.0f,
		-sin, cos, 0.0f,
		0.0f, 0.0f, 1.0f);
}

Matrix3x3 Matrix3x3::translate(const Vector2& position)
{
	return Matrix3x3(
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		position.x, position.y, 1.0f);
}

Matrix3x3 EvaEngine::operator+(const Matrix3x3& lhs, const Matrix3x3 rhs)
{
	Matrix3x3 matrix;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			matrix.m[i][j] = lhs.m[i][j] + rhs.m[i][j];
		}
	}
	return matrix;
}

Matrix3x3 EvaEngine::operator-(const Matrix3x3& lhs, const Matrix3x3 rhs)
{
	Matrix3x3 matrix;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			matrix.m[i][j] = lhs.m[i][j] - rhs.m[i][j];
		}
	}
	return matrix;
}

Matrix3x3 EvaEngine::operator*(const Matrix3x3& lhs, const float rhs)
{
	Matrix3x3 matrix;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			matrix.m[i][j] = lhs.m[i][j] * rhs;
		}
	}
	return matrix;
}

Matrix3x3 EvaEngine::operator*(const float lhs, const Matrix3x3& rhs)
{
	Matrix3x3 matrix;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			matrix.m[i][j] = lhs * rhs.m[i][j];
		}
	}
	return matrix;
}

Matrix3x3 EvaEngine::operator*(const Matrix3x3& lhs, const Matrix3x3 rhs)
{
	Matrix3x3 matrix;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			matrix.m[i][j] = 0;
			for (int k = 0; k < 3; ++k) {
				matrix.m[i][j] += lhs.m[i][k] * rhs.m[k][j];
			}
		}
	}
	return matrix;
}

Vector2 EvaEngine::operator*(const Vector2& lhs, const Matrix3x3 rhs)
{
	Vector2 matrix;
	Vector2 vec;
	vec.x = lhs.x * rhs.m[0][0] + lhs.y * rhs.m[1][0] + rhs.m[2][0];
	vec.y = lhs.x * rhs.m[0][1] + lhs.y * rhs.m[1][1] + rhs.m[2][1];
	return vec;
}

std::ostream& EvaEngine::operator<<(std::ostream& out, const Matrix3x3& rhs)
{
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			out << rhs.m[i][j];
			if (j < (3 - 1)) {
				out << " ";
			}
			else {
				out << std::endl;
			}
		}
	}
	return out;
}