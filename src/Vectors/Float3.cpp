
#include "Float3.h"
#include "Float2.h"
#include "Float4.h"
#include <cmath>

float Float3::length() {
    return std::sqrt(x * x + y * y + z * z);
}

Float3 Float3::unit() {
    return *this * (1 / length());
}

Float3::Float3(Float2 v1, float z) : x(v1.x), y(v1.y), z(z) {
}

Float3::Float3(float x, float y, float z) : x(x), y(y), z(z) {
}

Float3::Float3() : x(0), y(0), z(0) {
}

Float3::Float3(Float4 v1) : x(v1.x), y(v1.y), z(v1.z) {
}

Float3 Float3::operator+(const Float3 &v2) const {
    Float3 res(x + v2.x, y + v2.y, z + v2.z);
    return res;
}

Float3 Float3::operator-(const Float3 &v2) const {
    Float3 res(x - v2.x, y - v2.y, z - v2.z);
    return res;
}

Float3 Float3::operator-() const {
    Float3 res(-x, -y, -z);
    return res;
}

Float3 Float3::operator*(const float scalar) const {
    Float3 res(x * scalar, y * scalar, z * scalar);
    return res;
}

Float3 Float3::operator/(const float scalar) const {
    Float3 res(x /scalar, y / scalar, z / scalar);
    return res;}
