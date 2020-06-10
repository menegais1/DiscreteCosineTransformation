#ifndef ITRANSFORMABLE_H
#define ITRANSFORMABLE_H

#include "../Vectors/Float3.h"

class ITransformable {
public:
    virtual void translate(Float3) = 0;

    virtual void rotate(float, Float3) = 0;

    virtual void rescale(Float3, Float3) = 0;
};

#endif
