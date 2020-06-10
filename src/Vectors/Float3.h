#ifndef FLOAT3_H
#define FLOAT3_H

class Float2;

class Float4;

class Float3 {
public:
    float x, y, z;

    float length();

    Float3 unit();

    Float3(Float2, float);

    Float3(float, float, float);

    Float3();

    Float3(Float4);

    Float3 operator+(const Float3 &) const;

    Float3 operator-(const Float3 &) const;

    Float3 operator-() const;

    Float3 operator*(const float) const;

    Float3 operator/(const float) const;
};

#endif