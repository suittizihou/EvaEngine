#pragma once

#include <cmath>
#include <limits>

#undef max
#undef min

namespace EvaEngine {
	struct Mathf {
	public:
		// �~����
		static float pi() {
			return 3.14159265358979f;
		}
		// �x���烉�W�A���ɕϊ�����萔
		static float deg_to_rad() {
			return  pi() * 2.0f / 360.0f;
		}
		// ���W�A������x�ɕϊ�����萔
		static float rad_to_deg() {
			return 1.0f / deg_to_rad();
		}
		// f �̕�����Ԃ��܂�
		static float sign(float f) {
			return f >= 0.0f ? 1.0f : -1.0f;
		}
		// �������\�����܂�
		static float infinity() {
			return std::numeric_limits<float>::infinity();
		}
		// ���̖������\�����܂�
		static float negative_infinity() {
			return -std::numeric_limits<float>::infinity();
		}
		// �^����ꂽ�ŏ� float �l�ƍő� float �l�͈̔͂ɒl�𐧌����܂��B
		static float clamp(float value, float min, float max) {
			return (value < min) ? min : (value > max) ? max : value;
		}
		// 0 �� 1 �̊Ԃɒl�𐧌����A���̒l��Ԃ��܂��B
		static float clamp01(float value) {
			return clamp(value, 0.0f, 1.0f);
		}
		// current ���� target �܂ŁAmaxDelta �̃X�s�[�h�ňړ����܂�
		static float move_towards(float current, float target, float max_delta) {
			if (std::abs(target - current) <= max_delta)
				return target;
			return current + sign(target - current) * max_delta;
		}
		// ���� x �ȉ��ōő�̐����l�𓾂܂��B�i���֐��j
		static float floor(const float value) {
			return std::floor(value);
		}
		// �ő�l��Ԃ�
		static float max(float a, float b) { return a > b ? a : b; }
		// �ŏ��l��Ԃ�
		static float min(float a, float b) { return (a >= b) ? b : a; }
		// �ő���񐔂�Ԃ�
		static int gcd(int a, int b) {
			if (b == 0) return a;
			else return gcd(b, a % b);
		}
		// �ŏ����񐔂�Ԃ�
		static int lcm(int a, int b) {
			return a * b / gcd(a, b);
		}
		// �K���} (sRGB) ���烊�j�A�̐F��Ԃ֒l��ϊ����܂��B
		static float gamma_to_linear_space(const float value) {
			if (value <= 0.04045f)
				return value / 12.92f;
			else if (value < 1.0f)
				return pow((value + 0.055f) / 1.055F, 2.4f);
			else
				return pow(value, 2.2f);
		}
		// ���j�A����K���} (sRGB) �̐F��Ԃ֒l��ϊ����܂��B
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