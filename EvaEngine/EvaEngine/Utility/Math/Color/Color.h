#pragma once

#include <string>

namespace EvaEngine {
    struct Vector4;

    struct Color
    {
        // Red component of the color.
        float r{};
        // Green component of the color.
        float g{};
        // Blue component of the color.
        float b{};
        // Alpha component of the color.
        float a{};


        // �w�肳�ꂽr�Ag�Ab�Aa�R���|�[�l���g���g�p���ĐV�����F���쐬���܂��B
        Color(const float r, const float g, const float b, const float a);
        // �w�肳�ꂽr�Ag�Ab�R���|�[�l���g���g�p���ĐV�����F���쐬���A/ a /��1�ɐݒ肵�܂��B
        Color(const float r, const float g, const float b);

        // ������ɕϊ����܂��B
        std::string ToString();

        // ����������r���܂��B
        bool Equals(const Color& other);

        // �F/ a /��/ b /�̊Ԃ�/ t /�ŕ�Ԃ��܂��B
        static Color Lerp(Color a, Color b, float t);
        // ��Ԋ֐����N�����v�����ɁA�F / a / �� / b / �̊Ԃ� / t / �ŕ�Ԃ��܂��B
        static Color LerpUnclamped(Color a, Color b, float t);

        // RGB�R���|�[�l���g����Z����Ă��邪�A�A���t�@�͕ύX����Ă��Ȃ��V�����F��Ԃ��܂��B
        Color RGBMultiplied(float multiplier);
        // RGB�R���|�[�l���g����Z����Ă��邪�A�A���t�@�͕ύX����Ă��Ȃ��V�����F��Ԃ��܂��B
        Color AlphaMultiplied(float multiplier);
        //  RGB�R���|�[�l���g����Z����Ă��邪�A�A���t�@�͕ύX����Ă��Ȃ��V�����F��Ԃ��܂��B
        Color RGBMultiplied(Color multiplier);

        // RGBA(1, 0, 0, 1)�Ɠ����Ӗ�
        static Color Red();
        // RGBA(0, 1, 0, 1)�Ɠ����Ӗ�
        static Color Green();
        // RGBA(0, 0, 1, 1)�Ɠ����Ӗ�
        static Color Blue();
        // RGBA(1, 1, 1, 1)�Ɠ����Ӗ�
        static Color White();
        // RGBA(0, 0, 0, 1)�Ɠ����Ӗ�
        static Color Black();
        // RGBA(1, 0.92, 0.016, 1)�Ɠ����Ӗ�
        static Color Yellow();
        // RGBA(0, 1, 1, 1)�Ɠ����Ӗ�
        static Color Cyan();
        // RGBA(1, 0, 1, 1)�Ɠ����Ӗ�
        static Color Magenta();
        // RGBA(0.5, 0.5, 0.5, 1)�Ɠ����Ӗ�
        static Color Gray();
        // RGBA(0.5, 0.5, 0.5, 1)�Ɠ����Ӗ�
        static Color Grey();
        // RGBA(0, 0, 0, 0)�Ɠ����Ӗ�
        static Color Clear();

        // �O���[�X�P�[����Ԃ��܂��B
        float GrayScale();
        // sRGB�J���[�̐��`�l��Ԃ��܂��B
        Color Linear() const;
        // �K���}�J�[�u���K�p���ꂽ�F�̃o�[�W������Ԃ��܂��B
        Color Gamma() const;
        // �F�����l�̍ő�l��Ԃ��܂�
        float MaxColorComponent() const;
        // Vector4�ւ̈ÖكL���X�g
        operator Vector4() const;
        float operator[](int index) const;
        float& operator[](int index);

        // RGB��HSV�ɕϊ����܂�
        static void RGBToHSV(const Color& rgbColor, float* H, float* S, float* V);

        static void RGBToHSVHelper(float offset, float dominantcolor, float colorone, float colortwo, float* H, float* S, float* V);

        static Color HSVToRGB(float H, float S, float V);

            // Convert a set of HSV values to an RGB Color.
        static Color HSVToRGB(float H, float S, float V, bool hdr);
    };

    // ������Z�q�̃I�[�o�[���[�h
    Color& operator += (Color& lhs, const Color& rhs);
    Color& operator -= (Color& lhs, const Color& rhs);
    Color& operator *= (Color& lhs, float rhs);
    Color& operator /= (Color& lhs, float rhs);

    // �Q�����Z�q�I�[�o�[���[�h
    Color operator+(const Color& lhs, const Color& rhs);
    Color operator-(const Color& lhs, const Color& rhs);
    Color operator*(const Color& lhs, const Color& rhs);
    Color operator*(const Color& lhs, float rhs);
    Color operator*(float lhs, const Color& rhs);
    Color operator/(const Color& lhs, float rhs);

    // ��r���Z�q�̃I�[�o�[���[�h
    bool operator == (const Color& lhs, const Color& rhs);
    bool operator != (const Color& lhs, const Color& rhs);
}