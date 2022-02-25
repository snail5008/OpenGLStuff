#pragma once

// CURRENTLY UNUSED, IN FUTURE WILL IMPROVE AND REPLACE USING GLM

#include <iostream>
#include <cmath>

class Vec2 {
public:
	float x, y;
public:
	Vec2(float x_value, float y_value) : x(0), y(0) {
		x = x_value;
		y = y_value;
	}

	Vec2(float both_values) : x(0), y(0) {
		x = both_values;
		y = both_values;
	}

	Vec2() : x(0), y(0) {
		x = 0;
		y = 0;
	}

	float length() {
		return sqrtf(pow(x, 2)+pow(y, 2));
	}

	Vec2 add_scalar(float value) {
		return Vec2(x + value, y + value);
	}

	Vec2 subtract_scalar(float value) {
		return Vec2(x - value, y - value);
	}

	Vec2 multiply_scalar(float value) {
		return Vec2(x * value, y * value);
	}

	Vec2 divide_scalar(float value) {
		return Vec2(x / value, y / value);
	}

	Vec2 negate() {
		return Vec2(-x, -y);
	}

	Vec2 add_vec(Vec2 vec) {
		return Vec2(x + vec.x, y + vec.y);
	}

	Vec2 subtract_vec(Vec2 vec) {
		return Vec2(x - vec.x, y - vec.y);
	}

	float dot_product(Vec2 vec) {
		return (x * vec.x) + (y * vec.y);
	}


	Vec2 operator+(float val) {
		return add_scalar(val);
	}

	Vec2 operator-(float val) {
		return subtract_scalar(val);
	}

	Vec2 operator/(float val) {
		return divide_scalar(val);
	}

	Vec2 operator*(float val) {
		return multiply_scalar(val);
	}


	Vec2 operator+(Vec2 vec) {
		return add_vec(vec);
	}

	Vec2 operator-(Vec2 vec) {
		return subtract_vec(vec);
	}
};

std::ostream& operator<<(std::ostream& os, const Vec2& vec) {
	os << "Vec2{" << vec.x << ", " << vec.y << "}";
	return os;
}