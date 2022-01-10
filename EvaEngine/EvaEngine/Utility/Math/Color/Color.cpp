#include "Color.h"
#include "../Vector3/Vector3.h"
#include "../Vector4/Vector4.h"
#include "../Mathf/Mathf.h"
#include "../../../System/DebugLog/DebugLog.h"

#undef small
#undef max

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

void EvaEngine::Color::RGBToHSV(const Color& rgbColor, float* H, float* S, float* V)
{
    // when blue is highest valued
    if ((rgbColor.b > rgbColor.g) && (rgbColor.b > rgbColor.r))
        RGBToHSVHelper((float)4, rgbColor.b, rgbColor.r, rgbColor.g, H, S, V);
    //when green is highest valued
    else if (rgbColor.g > rgbColor.r)
        RGBToHSVHelper((float)2, rgbColor.g, rgbColor.b, rgbColor.r, H, S, V);
    //when red is highest valued
    else
        RGBToHSVHelper((float)0, rgbColor.r, rgbColor.g, rgbColor.b, H, S, V);
}

void EvaEngine::Color::RGBToHSVHelper(float offset, float dominantcolor, float colorone, float colortwo, float* H, float* S, float* V)
{
    *V = dominantcolor;
    //we need to find out which is the minimum color
    if (V != 0)
    {
        //we check which color is smallest
        float small = 0;
        if (colorone > colortwo) small = colortwo;
        else small = colorone;

        float diff = *V - small;

        //if the two values are not the same, we compute the like this
        if (diff != 0)
        {
            //S = max-min/max
            *S = diff / *V;
            //H = hue is offset by X, and is the difference between the two smallest colors
            *H = offset + ((colorone - colortwo) / diff);
        }
        else
        {
            //S = 0 when the difference is zero
            S = 0;
            //H = 4 + (R-G) hue is offset by 4 when blue, and is the difference between the two smallest colors
            *H = offset + (colorone - colortwo);
        }

        *H /= 6;

        //conversion values
        if (*H < 0)
            *H += 1.0f;
    }
    else
    {
        *S = 0;
        *H = 0;
    }
}

Color EvaEngine::Color::HSVToRGB(float H, float S, float V)
{
    return HSVToRGB(H, S, V, true);
}

Color EvaEngine::Color::HSVToRGB(float H, float S, float V, bool hdr)
{
    Color retval = Color::White();
    if (S == 0)
    {
        retval.r = V;
        retval.g = V;
        retval.b = V;
    }
    else if (V == 0)
    {
        retval.r = 0;
        retval.g = 0;
        retval.b = 0;
    }
    else
    {
        retval.r = 0;
        retval.g = 0;
        retval.b = 0;

        //crazy hsv conversion
        float t_S, t_V, h_to_floor;

        t_S = S;
        t_V = V;
        h_to_floor = H * 6.0f;

        int temp = (int)Mathf::floor(h_to_floor);
        float t = h_to_floor - ((float)temp);
        float var_1 = (t_V) * (1 - t_S);
        float var_2 = t_V * (1 - t_S * t);
        float var_3 = t_V * (1 - t_S * (1 - t));

        switch (temp)
        {
        case 0:
            retval.r = t_V;
            retval.g = var_3;
            retval.b = var_1;
            break;

        case 1:
            retval.r = var_2;
            retval.g = t_V;
            retval.b = var_1;
            break;

        case 2:
            retval.r = var_1;
            retval.g = t_V;
            retval.b = var_3;
            break;

        case 3:
            retval.r = var_1;
            retval.g = var_2;
            retval.b = t_V;
            break;

        case 4:
            retval.r = var_3;
            retval.g = var_1;
            retval.b = t_V;
            break;

        case 5:
            retval.r = t_V;
            retval.g = var_1;
            retval.b = var_2;
            break;

        case 6:
            retval.r = t_V;
            retval.g = var_3;
            retval.b = var_1;
            break;

        case -1:
            retval.r = t_V;
            retval.g = var_1;
            retval.b = var_2;
            break;
        }

        if (!hdr)
        {
            retval.r = Mathf::clamp(retval.r, 0.0f, 1.0f);
            retval.g = Mathf::clamp(retval.g, 0.0f, 1.0f);
            retval.b = Mathf::clamp(retval.b, 0.0f, 1.0f);
        }
    }
    return retval;
}

EvaEngine::Color::operator Vector4() const { return Vector4(r, g, b, a); }

EvaEngine::Color::operator Vector3() const { return Vector3(r, g, b); }

EvaEngine::Color::operator DirectX::XMVECTOR() const { return DirectX::XMLoadFloat4(&vec); }

float EvaEngine::Color::operator[](int index) const
{
    switch (index)
    {
    case 0: return r;
    case 1: return g;
    case 2: return b;
    case 3: return a;
    default:
        DebugLog::LogError("Invalid Color index(" + std::to_string(index) + ")!");
    }
}

float& EvaEngine::Color::operator[](int index)
{
    switch (index)
    {
    case 0: return r;
    case 1: return g;
    case 2: return b;
    case 3: return a;
    default:
        DebugLog::LogError("Invalid Color index(" + std::to_string(index) + ")!");
    }
}

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