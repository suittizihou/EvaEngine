#pragma once

#include <string>
#include <DirectXMath.h>

namespace EvaEngine {
    struct Vector3;
    struct Vector4;

    struct Color
    {
        union {
            DirectX::XMFLOAT4 vec;
            struct { float r, g, b, a; };
            float v[4];
        };

        // 指定されたr、g、b、aコンポーネントを使用して新しい色を作成します。
        Color(const float r, const float g, const float b, const float a);
        // 指定されたr、g、bコンポーネントを使用して新しい色を作成し、/ a /を1に設定します。
        Color(const float r = 1.0f, const float g = 1.0f, const float b = 1.0f);

        // 文字列に変換します。
        std::string ToString();

        // 等しいか比較します。
        bool Equals(const Color& other);

        // 色/ a /と/ b /の間を/ t /で補間します。
        static Color Lerp(Color a, Color b, float t);
        // 補間関数をクランプせずに、色 / a / と / b / の間を / t / で補間します。
        static Color LerpUnclamped(Color a, Color b, float t);

        // RGBコンポーネントが乗算されているが、アルファは変更されていない新しい色を返します。
        Color RGBMultiplied(float multiplier);
        // RGBコンポーネントが乗算されているが、アルファは変更されていない新しい色を返します。
        Color AlphaMultiplied(float multiplier);
        //  RGBコンポーネントが乗算されているが、アルファは変更されていない新しい色を返します。
        Color RGBMultiplied(Color multiplier);

        // RGBA(1, 0, 0, 1)と同じ意味
        static Color Red();
        // RGBA(0, 1, 0, 1)と同じ意味
        static Color Green();
        // RGBA(0, 0, 1, 1)と同じ意味
        static Color Blue();
        // RGBA(1, 1, 1, 1)と同じ意味
        static Color White();
        // RGBA(0, 0, 0, 1)と同じ意味
        static Color Black();
        // RGBA(1, 0.92, 0.016, 1)と同じ意味
        static Color Yellow();
        // RGBA(0, 1, 1, 1)と同じ意味
        static Color Cyan();
        // RGBA(1, 0, 1, 1)と同じ意味
        static Color Magenta();
        // RGBA(0.5, 0.5, 0.5, 1)と同じ意味
        static Color Gray();
        // RGBA(0.5, 0.5, 0.5, 1)と同じ意味
        static Color Grey();
        // RGBA(0, 0, 0, 0)と同じ意味
        static Color Clear();

        // グレースケールを返します。
        float GrayScale();
        // sRGBカラーの線形値を返します。
        Color Linear() const;
        // ガンマカーブが適用された色のバージョンを返します。
        Color Gamma() const;
        // 色成分値の最大値を返します
        float MaxColorComponent() const;

        // RGBをHSVに変換します
        static void RGBToHSV(const Color& rgbColor, float* H, float* S, float* V);

        static void RGBToHSVHelper(float offset, float dominantcolor, float colorone, float colortwo, float* H, float* S, float* V);

        static Color HSVToRGB(float H, float S, float V);

            // Convert a set of HSV values to an RGB Color.
        static Color HSVToRGB(float H, float S, float V, bool hdr);

        // Vector4への暗黙キャスト
        operator Vector4() const;
        // Vector3への暗黙キャスト
        operator Vector3() const;
        // XMVECTORへの暗黙キャスト
        operator DirectX::XMVECTOR() const;
        float operator[](int index) const;
        float& operator[](int index);
    };

    // 代入演算子のオーバーロード
    Color& operator += (Color& lhs, const Color& rhs);
    Color& operator -= (Color& lhs, const Color& rhs);
    Color& operator *= (Color& lhs, float rhs);
    Color& operator /= (Color& lhs, float rhs);

    // ２項演算子オーバーロード
    Color operator+(const Color& lhs, const Color& rhs);
    Color operator-(const Color& lhs, const Color& rhs);
    Color operator*(const Color& lhs, const Color& rhs);
    Color operator*(const Color& lhs, float rhs);
    Color operator*(float lhs, const Color& rhs);
    Color operator/(const Color& lhs, float rhs);

    // 比較演算子のオーバーロード
    bool operator == (const Color& lhs, const Color& rhs);
    bool operator != (const Color& lhs, const Color& rhs);
}