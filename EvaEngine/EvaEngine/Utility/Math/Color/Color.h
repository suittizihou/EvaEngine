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


        // Constructs a new Color with given r,g,b,a components.
        Color(const float r, const float g, const float b, const float a);

        // Constructs a new Color with given r,g,b components and sets /a/ to 1.
        Color(const float r, const float g, const float b);

        /// *listonly*
        std::string ToString();

        bool Equals(const Color& other);

        // Interpolates between colors /a/ and /b/ by /t/.
        static Color Lerp(Color a, Color b, float t);

        // Interpolates between colors /a/ and /b/ by /t/ without clamping the interpolant
        static Color LerpUnclamped(Color a, Color b, float t);

        // Returns new color that has RGB components multiplied, but leaving alpha untouched.
        Color RGBMultiplied(float multiplier);
        // Returns new color that has RGB components multiplied, but leaving alpha untouched.
        Color AlphaMultiplied(float multiplier);
        // Returns new color that has RGB components multiplied, but leaving alpha untouched.
        Color RGBMultiplied(Color multiplier);

        // Solid red. RGBA is (1, 0, 0, 1).
        static Color Red();
        // Solid green. RGBA is (0, 1, 0, 1).
        static Color Green();
        // Solid blue. RGBA is (0, 0, 1, 1).
        static Color Blue();
        // Solid white. RGBA is (1, 1, 1, 1).
        static Color White();
        // Solid black. RGBA is (0, 0, 0, 1).
        static Color Black();
        // Yellow. RGBA is (1, 0.92, 0.016, 1), but the color is nice to look at!
        static Color Yellow();
        // Cyan. RGBA is (0, 1, 1, 1).
        static Color Cyan();
        // Magenta. RGBA is (1, 0, 1, 1).
        static Color Magenta();
        // Gray. RGBA is (0.5, 0.5, 0.5, 1).
        static Color Gray();
        // English spelling for ::ref::gray. RGBA is the same (0.5, 0.5, 0.5, 1).
        static Color Grey();
        // Completely transparent. RGBA is (0, 0, 0, 0).
        static Color Clear();

        // The grayscale value of the color (RO)
        float GrayScale();

        // A version of the color that has had the inverse gamma curve applied
        Color Linear() const;

            // A version of the color that has had the gamma curve applied
        Color Gamma() const;

        float MaxColorComponent() const;

        // Vector4への暗黙キャスト
        operator Vector4() const;

                   // // Access the r, g, b,a components using [0], [1], [2], [3] respectively.
                   //float this[int index]
                   // {
                   //     get
                   //     {
                   //         switch (index)
                   //         {
                   //             case 0: return r;
                   //             case 1: return g;
                   //             case 2: return b;
                   //             case 3: return a;
                   //             default:
                   //                 throw new IndexOutOfRangeException("Invalid Color index(" + index + ")!");
                   //         }
                   //     }

                   //     set
                   //     {
                   //         switch (index)
                   //         {
                   //             case 0: r = value; break;
                   //             case 1: g = value; break;
                   //             case 2: b = value; break;
                   //             case 3: a = value; break;
                   //             default:
                   //                 throw new IndexOutOfRangeException("Invalid Color index(" + index + ")!");
                   //         }
                   //     }
                   // }

                   //     // Convert a color from RGB to HSV color space.
                   //        static void RGBToHSV(Color rgbColor, out float H, out float S, out float V)
                   //     {
                   //         // when blue is highest valued
                   //         if ((rgbColor.b > rgbColor.g) && (rgbColor.b > rgbColor.r))
                   //             RGBToHSVHelper((float)4, rgbColor.b, rgbColor.r, rgbColor.g, out H, out S, out V);
                   //         //when green is highest valued
                   //         else if (rgbColor.g > rgbColor.r)
                   //             RGBToHSVHelper((float)2, rgbColor.g, rgbColor.b, rgbColor.r, out H, out S, out V);
                   //         //when red is highest valued
                   //         else
                   //             RGBToHSVHelper((float)0, rgbColor.r, rgbColor.g, rgbColor.b, out H, out S, out V);
                   //     }

                   //     static void RGBToHSVHelper(float offset, float dominantcolor, float colorone, float colortwo, out float H, out float S, out float V)
                   //     {
                   //         V = dominantcolor;
                   //         //we need to find out which is the minimum color
                   //         if (V != 0)
                   //         {
                   //             //we check which color is smallest
                   //             float small = 0;
                   //             if (colorone > colortwo) small = colortwo;
                   //             else small = colorone;

                   //             float diff = V - small;

                   //             //if the two values are not the same, we compute the like this
                   //             if (diff != 0)
                   //             {
                   //                 //S = max-min/max
                   //                 S = diff / V;
                   //                 //H = hue is offset by X, and is the difference between the two smallest colors
                   //                 H = offset + ((colorone - colortwo) / diff);
                   //             }
                   //             else
                   //             {
                   //                 //S = 0 when the difference is zero
                   //                 S = 0;
                   //                 //H = 4 + (R-G) hue is offset by 4 when blue, and is the difference between the two smallest colors
                   //                 H = offset + (colorone - colortwo);
                   //             }

                   //             H /= 6;

                   //             //conversion values
                   //             if (H < 0)
                   //                 H += 1.0f;
                   //         }
                   //         else
                   //         {
                   //             S = 0;
                   //             H = 0;
                   //         }
                   //     }

                   //    static Color HSVToRGB(float H, float S, float V)
                   //     {
                   //         return HSVToRGB(H, S, V, true);
                   //     }

                   //     // Convert a set of HSV values to an RGB Color.
                   //    static Color HSVToRGB(float H, float S, float V, bool hdr)
                   //     {
                   //         Color retval = Color.white;
                   //         if (S == 0)
                   //         {
                   //             retval.r = V;
                   //             retval.g = V;
                   //             retval.b = V;
                   //         }
                   //         else if (V == 0)
                   //         {
                   //             retval.r = 0;
                   //             retval.g = 0;
                   //             retval.b = 0;
                   //         }
                   //         else
                   //         {
                   //             retval.r = 0;
                   //             retval.g = 0;
                   //             retval.b = 0;

                   //             //crazy hsv conversion
                   //             float t_S, t_V, h_to_floor;

                   //             t_S = S;
                   //             t_V = V;
                   //             h_to_floor = H * 6.0f;

                   //             int temp = (int)Mathf.Floor(h_to_floor);
                   //             float t = h_to_floor - ((float)temp);
                   //             float var_1 = (t_V) * (1 - t_S);
                   //             float var_2 = t_V * (1 - t_S * t);
                   //             float var_3 = t_V * (1 - t_S * (1 - t));

                   //             switch (temp)
                   //             {
                   //             case 0:
                   //                 retval.r = t_V;
                   //                 retval.g = var_3;
                   //                 retval.b = var_1;
                   //                 break;

                   //             case 1:
                   //                 retval.r = var_2;
                   //                 retval.g = t_V;
                   //                 retval.b = var_1;
                   //                 break;

                   //             case 2:
                   //                 retval.r = var_1;
                   //                 retval.g = t_V;
                   //                 retval.b = var_3;
                   //                 break;

                   //             case 3:
                   //                 retval.r = var_1;
                   //                 retval.g = var_2;
                   //                 retval.b = t_V;
                   //                 break;

                   //             case 4:
                   //                 retval.r = var_3;
                   //                 retval.g = var_1;
                   //                 retval.b = t_V;
                   //                 break;

                   //             case 5:
                   //                 retval.r = t_V;
                   //                 retval.g = var_1;
                   //                 retval.b = var_2;
                   //                 break;

                   //             case 6:
                   //                 retval.r = t_V;
                   //                 retval.g = var_3;
                   //                 retval.b = var_1;
                   //                 break;

                   //             case -1:
                   //                 retval.r = t_V;
                   //                 retval.g = var_1;
                   //                 retval.b = var_2;
                   //                 break;
                   //             }

                   //             if (!hdr)
                   //             {
                   //                 retval.r = Mathf.Clamp(retval.r, 0.0f, 1.0f);
                   //                 retval.g = Mathf.Clamp(retval.g, 0.0f, 1.0f);
                   //                 retval.b = Mathf.Clamp(retval.b, 0.0f, 1.0f);
                   //             }
                   //         }
                   //         return retval;
                   //     }
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