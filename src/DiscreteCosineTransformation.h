//
// Created by menegais1 on 14/06/2020.
//

#ifndef DISCRETECOSINETRANSFORMATION_DISCRETECOSINETRANSFORMATION_H
#define DISCRETECOSINETRANSFORMATION_DISCRETECOSINETRANSFORMATION_H


#include <vector>

class DiscreteCosineTransformation {
public:
    std::vector<float> forwardDCT(std::vector<float> values);
    std::vector<float> inverseDCT(std::vector<float> values);
    std::vector<float> difference(std::vector<float> originalValues, std::vector<float> convertedValues);
    std::vector<Float2> baseFunctions(int u,int samples, float step);
    std::vector<Float2> convertToValueTuple(std::vector<float> values);
private:
    float C(int w);
};

#endif //DISCRETECOSINETRANSFORMATION_DISCRETECOSINETRANSFORMATION_H
