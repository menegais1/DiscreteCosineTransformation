//
// Created by menegais1 on 14/06/2020.
//

#ifndef DISCRETECOSINETRANSFORMATION_DISCRETECOSINETRANSFORMATION_H
#define DISCRETECOSINETRANSFORMATION_DISCRETECOSINETRANSFORMATION_H


#include <vector>

class DiscreteCosineTransformation {
public:
    static std::vector<float> forwardDCT(std::vector<float> values);
    static std::vector<float> inverseDCT(std::vector<float> values);
    static std::vector<float> difference(std::vector<float> originalValues, std::vector<float> convertedValues);
    static std::vector<Float2> baseFunctions(int u,int samples, float step);
    static std::vector<float> generateQuantizationVector(int samples, int quantizationFactor);
    static std::vector<float> applyQuantization(std::vector<float> values,std::vector<float> quantizationVector,int quantizationFactor);
    static std::vector<Float2> convertToValueTuple(std::vector<float> values);
    static std::vector<float> applyInverseQuantization(std::vector<float> values, std::vector<float> quantizationVector, int quantizationFactor);
private:
    static float C(int w);


};

#endif //DISCRETECOSINETRANSFORMATION_DISCRETECOSINETRANSFORMATION_H
