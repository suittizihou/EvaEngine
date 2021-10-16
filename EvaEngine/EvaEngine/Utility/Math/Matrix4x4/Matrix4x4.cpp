#include "Matrix4x4.h"
#include "../Vector3/Vector3.h"
#include "..//Quaternion/Quaternion.h"
#include <iostream>
#include  <cmath>

using namespace EvaEngine;

Matrix4x4::Matrix4x4(float m11, float m12, float m13, float m14, float m21, float m22, float m23, float m24, float m31, float m32, float m33, float m34, float m41, float m42, float m43, float m44)
{
	m[0][0] = m11; m[0][1] = m12; m[0][2] = m13; m[0][3] = m14;
	m[1][0] = m21; m[1][1] = m22; m[1][2] = m23; m[1][3] = m24;
	m[2][0] = m31; m[2][1] = m32; m[2][2] = m33; m[2][3] = m34;
	m[3][0] = m41; m[3][1] = m42; m[3][2] = m43; m[3][3] = m44;
}

EvaEngine::Matrix4x4::Matrix4x4(float* matrix)
{
	memcpy(&m16[0], &matrix[0], sizeof(float) * 16);
}

Matrix4x4 Matrix4x4::zero()
{
	return Matrix4x4(
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f
	);
}

Matrix4x4 Matrix4x4::identity()
{
	return Matrix4x4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix4x4 Matrix4x4::inverse(const Matrix4x4& m)
{
	float a0 = m.m[0][0] * m.m[1][1] - m.m[0][1] * m.m[1][0];
	float a1 = m.m[0][0] * m.m[1][2] - m.m[0][2] * m.m[1][0];
	float a2 = m.m[0][0] * m.m[1][3] - m.m[0][3] * m.m[1][0];
	float a3 = m.m[0][1] * m.m[1][2] - m.m[0][2] * m.m[1][1];
	float a4 = m.m[0][1] * m.m[1][3] - m.m[0][3] * m.m[1][1];
	float a5 = m.m[0][2] * m.m[1][3] - m.m[0][3] * m.m[1][2];
	float b0 = m.m[2][0] * m.m[3][1] - m.m[2][1] * m.m[3][0];
	float b1 = m.m[2][0] * m.m[3][2] - m.m[2][2] * m.m[3][0];
	float b2 = m.m[2][0] * m.m[3][3] - m.m[2][3] * m.m[3][0];
	float b3 = m.m[2][1] * m.m[3][2] - m.m[2][2] * m.m[3][1];
	float b4 = m.m[2][1] * m.m[3][3] - m.m[2][3] * m.m[3][1];
	float b5 = m.m[2][2] * m.m[3][3] - m.m[2][3] * m.m[3][2];
	float det = a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0;
	if (det == 0.0f) {
		return m; // ‹ts—ñ‚ª‘¶Ý‚µ‚È‚¢!
	}
	float invDet = 1.0f / det;
	Matrix4x4 result = {
	(m.m[1][1] * b5 - m.m[1][2] * b4 + m.m[1][3] * b3) * invDet,
	(-m.m[0][1] * b5 + m.m[0][2] * b4 - m.m[0][3] * b3) * invDet,
	(m.m[3][1] * a5 - m.m[3][2] * a4 + m.m[3][3] * a3) * invDet,
	(-m.m[2][1] * a5 + m.m[2][2] * a4 - m.m[2][3] * a3) * invDet,
	(-m.m[1][0] * b5 + m.m[1][2] * b2 - m.m[1][3] * b1) * invDet,
	(m.m[0][0] * b5 - m.m[0][2] * b2 + m.m[0][3] * b1) * invDet,
	(-m.m[3][0] * a5 + m.m[3][2] * a2 - m.m[3][3] * a1) * invDet,
	(m.m[2][0] * a5 - m.m[2][2] * a2 + m.m[2][3] * a1) * invDet,
	(m.m[1][0] * b4 - m.m[1][1] * b2 + m.m[1][3] * b0) * invDet,
	(-m.m[0][0] * b4 + m.m[0][1] * b2 - m.m[0][3] * b0) * invDet,
	(m.m[3][0] * a4 - m.m[3][1] * a2 + m.m[3][3] * a0) * invDet,
	(-m.m[2][0] * a4 + m.m[2][1] * a2 - m.m[2][3] * a0) * invDet,
	(-m.m[1][0] * b3 + m.m[1][1] * b1 - m.m[1][2] * b0) * invDet,
	(m.m[0][0] * b3 - m.m[0][1] * b1 + m.m[0][2] * b0) * invDet,
	(-m.m[3][0] * a3 + m.m[3][1] * a1 - m.m[3][2] * a0) * invDet,
	(m.m[2][0] * a3 - m.m[2][1] * a1 + m.m[2][2] * a0) * invDet
	};
	return result;
}

Matrix4x4 Matrix4x4::scale(const Vector3& vector)
{
	return Matrix4x4(
		vector.x, 0.0f, 0.0f, 0.0f,
		0.0f, vector.y, 0.0f, 0.0f,
		0.0f, 0.0f, vector.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);

}

Matrix4x4 Matrix4x4::rotate(const Quaternion& q)
{
	float xx = q.x * q.x * 2.0f;
	float yy = q.y * q.y * 2.0f;
	float zz = q.z * q.z * 2.0f;
	float xy = q.x * q.y * 2.0f;
	float xz = q.x * q.z * 2.0f;
	float yz = q.y * q.z * 2.0f;
	float wx = q.w * q.x * 2.0f;
	float wy = q.w * q.y * 2.0f;
	float wz = q.w * q.z * 2.0f;
	return Matrix4x4{
	1.0f - yy - zz, xy + wz, xz - wy, 0.0f,
	xy - wz, 1.0f - xx - zz, yz + wx, 0.0f,
	xz + wy, yz - wx, 1.0f - xx - yy, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f };
}

Matrix4x4 Matrix4x4::rotate_x(float degree)
{
	float rad = degree * (3.14159265359f / 180.0f);
	float cos = std::cos(rad);
	float sin = std::sin(rad);

	return Matrix4x4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, cos, sin, 0.0f,
		0.0f, -sin, cos, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix4x4 Matrix4x4::rotate_y(float degree)
{
	float rad = degree * (3.14159265359f / 180.0f);
	float cos = std::cos(rad);
	float sin = std::sin(rad);

	return Matrix4x4(
		cos, 0.0f, -sin, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		sin, 0.0f, cos, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix4x4 Matrix4x4::rotate_z(float degree)
{
	float rad = degree * (3.14159265359f / 180.0f);
	float cos = std::cos(rad);
	float sin = std::sin(rad);

	return Matrix4x4(
		cos, sin, 0.0f, 0.0f,
		-sin, cos, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix4x4 Matrix4x4::translate(const Vector3& position)
{
	return Matrix4x4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		position.x, position.y, position.z, 1.0f
	);
}

Matrix4x4 Matrix4x4::look_at(const Vector3& eye, const Vector3& at, const Vector3& up)
{
	Vector3 z = (eye - at).normalized();
	Vector3 x = (Vector3::cross(up, z)).normalized();
	Vector3 y = Vector3::cross(z, x);
	return Matrix4x4(
		x.x, y.x, z.x, 0.0f,
		x.y, y.y, z.y, 0.0f,
		x.z, y.z, z.z, 0.0f,
		-Vector3::dot(eye, x), -Vector3::dot(eye, y), -Vector3::dot(eye, z), 1.0f
	);
}

Matrix4x4 Matrix4x4::perspective(float fov, float aspect, float znear, float zfar)
{
	float rad = fov * (3.14159265359f / 180.0f);
	float f = 1.0f / std::tan(rad / 2.0f);
	return Matrix4x4(
		f / aspect, 0.0f, 0.0f, 0.0f,
		0.0f, f, 0.0f, 0.0f,
		0.0f, 0.0f, (zfar + znear) / (znear - zfar), -1.0f,
		0.0f, 0.0f, (2.0f * zfar * znear) / (znear - zfar), 0.0f
	);
}

Vector3 Matrix4x4::multply_point(const Vector3& point) const
{
	float x = point.x * m[0][0] + point.y * m[1][0] + point.z * m[2][0] + m[3][0];
	float y = point.x * m[0][1] + point.y * m[1][1] + point.z * m[2][1] + m[3][1];
	float z = point.x * m[0][2] + point.y * m[1][2] + point.z * m[2][2] + m[3][2];
	float w = point.x * m[0][3] + point.y * m[1][3] + point.z * m[2][3] + m[3][3];
	return Vector3(x / w, y / w, z / w);
}

Vector3 Matrix4x4::multiply_point4x3(const Vector3& point) const
{
	float x = point.x * m[0][0] + point.y * m[1][0] + point.z * m[2][0] + m[3][0];
	float y = point.x * m[0][1] + point.y * m[1][1] + point.z * m[2][1] + m[3][1];
	float z = point.x * m[0][2] + point.y * m[1][2] + point.z * m[2][2] + m[3][2];
	return Vector3(x, y, z);
}

Vector3 Matrix4x4::multiply_vector(const Vector3& point) const
{
	float x = point.x * m[0][0] + point.y * m[1][0] + point.z * m[2][0];
	float y = point.x * m[0][1] + point.y * m[1][1] + point.z * m[2][1];
	float z = point.x * m[0][2] + point.y * m[1][2] + point.z * m[2][2];
	return Vector3(x, y, z);
}

Vector3 Matrix4x4::scale() const
{
	float x, y, z;
	x = Vector3(this->m[0][0], this->m[0][1], this->m[0][2]).magnitude();
	y = Vector3(this->m[1][0], this->m[1][1], this->m[1][2]).magnitude();
	z = Vector3(this->m[2][0], this->m[2][1], this->m[2][2]).magnitude();
	return Vector3(x, y, z);
}

Vector3 Matrix4x4::forward() const
{
	return Vector3(this->m[2][0], this->m[2][1], this->m[2][2]).normalized();
}

Vector3 Matrix4x4::left() const
{
	return Vector3(this->m[0][0], this->m[0][1], this->m[0][2]).normalized();
}

Vector3 Matrix4x4::upward() const
{
	return Vector3(this->m[1][0], this->m[1][1], this->m[1][2]).normalized();
}

Vector3 Matrix4x4::position() const
{
	return Vector3(this->m[3][0], this->m[3][1], this->m[3][2]);
}

Quaternion Matrix4x4::rotation() const
{
	Quaternion result;
	float tr = m[0][0] + m[1][1] + m[2][2] + 1.0f;
	if (tr >= 1.0f) {
		float fourD = 2.0f * std::sqrt(tr);
		result.x = (m[1][2] - m[2][1]) / fourD;
		result.y = (m[2][0] - m[0][2]) / fourD;
		result.z = (m[0][1] - m[1][0]) / fourD;
		result.w = fourD / 4.0f;
		return result;
	}
	int i = 0;
	if (m[0][0] <= m[1][1]) {
		i = 1;
	}
	if (m[2][2] > m[i][i]) {
		i = 2;
	}
	int j = (i + 1) % 3;
	int k = (j + 1) % 3;
	tr = m[i][i] - m[j][j] - m[k][k] + 1.0f;
	float fourD = 2.0f * std::sqrt(tr);
	float qa[4];
	qa[i] = fourD / 4.0f;
	qa[j] = (m[j][i] + m[i][j]) / fourD;
	qa[k] = (m[k][i] + m[i][k]) / fourD;
	qa[3] = (m[j][k] - m[k][j]) / fourD;
	result.x = qa[0];
	result.y = qa[1];
	result.z = qa[2];
	result.w = qa[3];
	return result;
}

Matrix4x4 Matrix4x4::inverse() const
{
	return Matrix4x4::inverse(*this);
}

Matrix4x4 Matrix4x4::transpose() const
{
	return Matrix4x4(
		m[0][0], m[1][0], m[2][0], m[3][0],
		m[0][1], m[1][1], m[2][1], m[3][1],
		m[0][2], m[1][2], m[2][2], m[3][2],
		m[0][3], m[1][3], m[2][3], m[3][3]
	);
}

Matrix4x4 Matrix4x4::TRS(const Vector3& t, const Quaternion& r, const Vector3& s)
{
	return Matrix4x4::scale(s) * Matrix4x4::rotate(r) * Matrix4x4::translate(t);
}

void Matrix4x4::set_TRS(const Vector3& t, const Quaternion& r, const Vector3& s)
{
	*this = TRS(t, r, s);
}

DirectX::XMMATRIX EvaEngine::Matrix4x4::to_XMMATRIX() const
{
	return DirectX::XMMATRIX(
		m[0][0], m[0][1], m[0][2], m[0][3],
		m[1][0], m[1][1], m[1][2], m[1][3],
		m[2][0], m[2][1], m[2][2], m[2][3],
		m[3][0], m[3][1], m[3][2], m[3][3]);
}

DirectX::XMMATRIX EvaEngine::Matrix4x4::to_XMMATRIX(const Matrix4x4& matrix)
{
	return matrix.to_XMMATRIX();
}

Matrix4x4 EvaEngine::Matrix4x4::to_Matrix4x4(const DirectX::XMMATRIX& matrix)
{
	return Matrix4x4(
		matrix.r[0].m128_f32[0], matrix.r[0].m128_f32[1], matrix.r[0].m128_f32[2], matrix.r[0].m128_f32[3],
		matrix.r[1].m128_f32[0], matrix.r[1].m128_f32[1], matrix.r[1].m128_f32[2], matrix.r[1].m128_f32[3],
		matrix.r[2].m128_f32[0], matrix.r[2].m128_f32[1], matrix.r[2].m128_f32[2], matrix.r[2].m128_f32[3],
		matrix.r[3].m128_f32[0], matrix.r[3].m128_f32[1], matrix.r[3].m128_f32[2], matrix.r[3].m128_f32[3]);
}

Matrix4x4 EvaEngine::operator+(const Matrix4x4& lhs, const Matrix4x4& rhs)
{
	Matrix4x4 result;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = lhs.m[i][j] + rhs.m[i][j];
		}
	}
	return result;
}

Matrix4x4 EvaEngine::operator-(const Matrix4x4& lhs, const Matrix4x4& rhs)
{
	Matrix4x4 result;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = lhs.m[i][j] - rhs.m[i][j];
		}
	}
	return result;
}

Matrix4x4 EvaEngine::operator*(const Matrix4x4& lhs, float rhs)
{
	Matrix4x4 result;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = lhs.m[i][j] * rhs;
		}
	}
	return result;
}

Matrix4x4 EvaEngine::operator*(float lhs, const Matrix4x4& rhs)
{
	Matrix4x4 result;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result.m[i][j] = lhs * rhs.m[i][j];
		}
	}
	return result;
}

Matrix4x4 EvaEngine::operator*(const Matrix4x4& lhs, const Matrix4x4& rhs)
{
	Matrix4x4 result;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = 0;
			for (int k = 0; k < 4; ++k) {
				result.m[i][j] += lhs.m[i][k] * rhs.m[k][j];
			}
		}
	}
	return result;
}

Vector3 EvaEngine::operator*(const Vector3& lhs, const Matrix4x4& rhs)
{
	return rhs.multply_point(lhs);
}

std::ostream& EvaEngine::operator<<(std::ostream& lhs, const Matrix4x4& rhs)
{
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			lhs << rhs.m[i][j];
			if (j < (4 - 1)) {
				lhs << " ";
			}
			else {
				lhs << std::endl;
			}
		}
	}
	return lhs;
}