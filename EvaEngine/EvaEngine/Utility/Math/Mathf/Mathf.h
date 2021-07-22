#pragma once

#include <cmath>
#include <limits>

#undef max
#undef min

namespace EvaEngine {
	struct Mathf {
	public:
		// 円周率
		static float pi() {
			return 3.14159265358979f;
		}
		// 度からラジアンに変換する定数
		static float deg_to_rad() {
			return  pi() * 2.0f / 360.0f;
		}
		// ラジアンから度に変換する定数
		static float rad_to_deg() {
			return 1.0f / deg_to_rad();
		}
		// f の符号を返します
		static float sign(float f) {
			return f >= 0.0f ? 1.0f : -1.0f;
		}
		// 無限大を表現します
		static float infinity() {
			return std::numeric_limits<float>::infinity();
		}
		// 負の無限大を表現します
		static float negative_infinity() {
			return -std::numeric_limits<float>::infinity();
		}
		// 与えられた最小 float 値と最大 float 値の範囲に値を制限します。
		static float clamp(float value, float min, float max) {
			return (value < min) ? min : (value > max) ? max : value;
		}
		// 0 と 1 の間に値を制限し、その値を返します。
		static float clamp01(float value) {
			return clamp(value, 0.0f, 1.0f);
		}
		// current から target まで、maxDelta のスピードで移動します
		static float move_towards(float current, float target, float max_delta) {
			if (std::abs(target - current) <= max_delta)
				return target;
			return current + sign(target - current) * max_delta;
		}
		// 最大値を返す
		static float max(float a, float b) { return a > b ? a : b; }
		// 最小値を返す
		static float min(float a, float b) { return (a >= b) ? b : a; }
		// ガンマ (sRGB) からリニアの色空間へ値を変換します。
		static float gamma_to_linear_space(const float value) {
			if (value <= 0.04045f)
				return value / 12.92f;
			else if (value < 1.0f)
				return pow((value + 0.055f) / 1.055F, 2.4f);
			else
				return pow(value, 2.2f);
		}
		// リニアからガンマ (sRGB) の色空間へ値を変換します。
		static float linear_to_gamma_space(const float value) {
			if (value <= 0.0f)
				return 0.0f;
			else if (value <= 0.0031308f)
				return 12.92f * value;
			else if (value < 1.0f)
				return 1.055f * pow(value, 0.4166667f) - 0.055f;
			else
				return pow(value, 0.45454545f);
		}
	};
}