#ifndef FLOAT4_H
#define FLOAT4_H

#include "Float3.h"

class Float4 {
public:
    float x, y, z, w;

    float length();

    Float4 unit();

    Float4(Float3, float);

    Float4(float, float, float, float);

    Float4();

    Float4 operator+(const Float4 &);

    Float4 operator*(const float);
};

#endif