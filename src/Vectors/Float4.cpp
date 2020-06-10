
#include "Float3.h"
#include "Float4.h"
#include <cmath>

float Float4::length() {
    return std::sqrt(x * x + y * y + z * z + w * w);
}

Float4 Float4::unit() {
    return *this * (1 / length());
}

Float4::Float4(Float3 v1, float w) : x(v1.x), y(v1.y), z(v1.z), w(w) {
}

Float4::Float4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {
}

Float4::Float4() : x(0), y(0), z(0), w(0) {
}

Float4 Float4::operator+(const Float4 &v2) {
    Float4 res(x + v2.x, y + v2.y, z + v2.z, w + v2.w);
    return res;
}

Float4 Float4::operator*(const float scalar) {
    Float4 res(x * scalar, y * scalar, z * scalar, w * scalar);
    return res;
}
