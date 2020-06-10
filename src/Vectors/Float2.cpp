
#include "Float2.h"
#include "Float3.h"
#include <cmath>

float Float2::length() {
    return std::sqrt(x * x + y * y);
}

Float2 Float2::unit() {
    return *this * (1 / length());
}

Float2::Float2(float x, float y) : x(x), y(y) {
}

Float2::Float2() : x(0), y(0) {
}

Float2::Float2(Float3 v1) : x(v1.x), y(v1.y) {
}

Float2 Float2::operator+(const Float2 &v2) {
    Float2 res(x + v2.x, y + v2.y);
    return res;
}

Float2 Float2::operator-(const Float2 &v2) {
    Float2 res(x - v2.x, y - v2.y);
    return res;
}

Float2 Float2::operator*(const float scalar) {
    Float2 res(x * scalar, y * scalar);
    return res;
}

Float2 Float2::operator-() const {
    Float2 res(-x, -y);
    return res;
}