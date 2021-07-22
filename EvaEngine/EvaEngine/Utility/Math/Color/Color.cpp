#include "Color.h"
#include "../Vector4/Vector4.h"
#include "../Mathf/Mathf.h"

using namespace EvaEngine;

EvaEngine::Color::Color(const float r, const float g, const float b, const float a)
{
	this->r = r; this->g = g; this->b = b; this->a = a;
}

EvaEngine::Color::Color(const float r, const float g, const float b)
{
	this->r = r; this->g = g; this->b = b; this->a = 1.0f;
}

std::string EvaEngine::Color::ToString()
{
	return std::string("R : " + std::to_string(r) + " ,G : " + std::to_string(g) + " ,B : " + std::to_string(b) + " ,A : " + std::to_string(a));
}

bool EvaEngine::Color::Equals(const Color& other)
{
	return r == other.r && g == other.g && b == other.b && a == other.a;
}

Color EvaEngine::Color::Lerp(Color a, Color b, float t)
{
    t = Mathf::clamp01(t);
    return Color(
        a.r + (b.r - a.r) * t,
        a.g + (b.g - a.g) * t,
        a.b + (b.b - a.b) * t,
        a.a + (b.a - a.a) * t
    );
}

Color EvaEngine::Color::LerpUnclamped(Color a, Color b, float t)
{
    return Color(
        a.r + (b.r - a.r) * t,
        a.g + (b.g - a.g) * t,
        a.b + (b.b - a.b) * t,
        a.a + (b.a - a.a) * t
    );
}

Color EvaEngine::Color::RGBMultiplied(float multiplier) { return Color(r * multiplier, g * multiplier, b * multiplier, a); }

Color EvaEngine::Color::AlphaMultiplied(float multiplier) { return Color(r, g, b, a * multiplier); }

Color EvaEngine::Color::RGBMultiplied(Color multiplier) { return Color(r * multiplier.r, g * multiplier.g, b * multiplier.b, a); }

Color EvaEngine::Color::Red() { return Color(1.0f, 0.0f, 0.0f, 1.0f); }
Color EvaEngine::Color::Green() { return Color(0.0f, 1.0f, 0.0f, 1.0f); }
Color EvaEngine::Color::Blue() { return Color(0.0f, 0.0f, 1.0f, 1.0f); }
Color EvaEngine::Color::White() { return Color(1.0f, 1.0f, 1.0f, 1.0f); }
Color EvaEngine::Color::Black() { return Color(0.0f, 0.0f, 0.0f, 1.0f); }
Color EvaEngine::Color::Yellow() { return Color(1.0f, 235.0f / 255.0f, 4.0f / 255.0f, 1.0f); }
Color EvaEngine::Color::Cyan() { return Color(0.0f, 1.0f, 1.0f, 1.0f); }
Color EvaEngine::Color::Magenta() { return Color(1.0f, 0.0f, 1.0f, 1.0f); }
Color EvaEngine::Color::Gray() { return Color(.5f, .5f, .5f, 1.0f); }
Color EvaEngine::Color::Grey() { return Color(.5f, .5f, .5f, 1.0f); }
Color EvaEngine::Color::Clear() { return Color(0.0f, 0.0f, 0.0f, 0.0f); }

float EvaEngine::Color::GrayScale() { return 0.299f * r + 0.587f * g + 0.114f * b; }

Color EvaEngine::Color::Linear() const { return Color(Mathf::gamma_to_linear_space(r), Mathf::gamma_to_linear_space(g), Mathf::gamma_to_linear_space(b), a); }

Color EvaEngine::Color::Gamma() const { return Color(Mathf::linear_to_gamma_space(r), Mathf::linear_to_gamma_space(g), Mathf::linear_to_gamma_space(b), a); }

float EvaEngine::Color::MaxColorComponent() const { return Mathf::max(Mathf::max(r, g), b); }

EvaEngine::Color::operator Vector4() const { return Vector4(r, g, b, a); }

Color& EvaEngine::operator+=(Color& lhs, const Color& rhs)
{
    lhs.r += rhs.r;
    lhs.b += rhs.b;
    lhs.b += rhs.b;
    lhs.a += rhs.a;
    return lhs;
}

Color& EvaEngine::operator-=(Color& lhs, const Color& rhs)
{
    lhs.r -= rhs.r;
    lhs.b -= rhs.b;
    lhs.b -= rhs.b;
    lhs.a -= rhs.a;
    return lhs;
}

Color& EvaEngine::operator*=(Color& lhs, float rhs)
{
    lhs.r *= rhs;
    lhs.b *= rhs;
    lhs.b *= rhs;
    lhs.a *= rhs;
    return lhs;
}

Color& EvaEngine::operator/=(Color& lhs, float rhs)
{
    if (rhs == 0.0f) {
        lhs = Color::Clear();
    }
    else {
        lhs.r /= rhs;
        lhs.b /= rhs;
        lhs.b /= rhs;
        lhs.a /= rhs;
    }

    return lhs;
}

Color EvaEngine::operator+(const Color& lhs, const Color& rhs) { return Color(lhs.r + rhs.r, lhs.g + rhs.g, lhs.b + rhs.b, lhs.a + rhs.a); }
Color EvaEngine::operator-(const Color& lhs, const Color& rhs) { return Color(lhs.r - rhs.r, lhs.g - rhs.g, lhs.b - rhs.b, lhs.a - rhs.a); }
Color EvaEngine::operator*(const Color& lhs, const Color& rhs) { return Color(lhs.r * rhs.r, lhs.g * rhs.g, lhs.b * rhs.b, lhs.a * rhs.a); }
Color EvaEngine::operator*(const Color& lhs, float rhs) { return Color(lhs.r * rhs, lhs.g * rhs, lhs.b * rhs, lhs.a * rhs); }
Color EvaEngine::operator*(float lhs, const Color& rhs) { return rhs * lhs; }
Color EvaEngine::operator/(const Color& lhs, float rhs) { return Color(lhs.r / rhs, lhs.g / rhs, lhs.b / rhs, lhs.a / rhs); }

bool EvaEngine::operator==(const Color& lhs, const Color& rhs) { return (Vector4)lhs == (Vector4)rhs; }
bool EvaEngine::operator!=(const Color& lhs, const Color& rhs) { return !(lhs == rhs); }