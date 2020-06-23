//
// Created by menegais1 on 14/06/2020.
//

#include <cmath>
#include <ctime>
#include "Utilities.h"
#include "DiscreteCosineTransformation.h"


std::vector<float> DiscreteCosineTransformation::forwardDCT(std::vector<float> values) {
    int m = values.size();
    std::vector<float> convertedValues(m);
    for (int u = 0; u < m; u++) {
        float fu = 0;
        for (int x = 0; x < m; x++) {
            fu += values[x] * C(u) * cos(((2 * x + 1) * u * PI) / (2.0 * m));
        }
        convertedValues[u] = (fu * pow(2.0 / (float) m, 1.0 / 2.0));
    }

    return convertedValues;
}

float DiscreteCosineTransformation::C(int w) {
    if (w == 0) return 1.0 / sqrt(2);
    return 1;
}

std::vector<float> DiscreteCosineTransformation::inverseDCT(std::vector<float> values) {
    int m = values.size();
    std::vector<float> convertedValues(m);
    for (int x = 0; x < m; x++) {
        float fx = 0;
        for (int u = 0; u < m; u++) {

            fx += values[u] * C(u) * cos(((2 * x + 1) * u * PI) / (2.0 * m));
        }
        convertedValues[x] = ((fx * pow(2.0 / (float) m, 1.0 / 2.0)));
    }

    return convertedValues;
}

std::vector<float>
DiscreteCosineTransformation::difference(std::vector<float> originalValues, std::vector<float> convertedValues) {
    std::vector<float> diff(originalValues.size());

    for (int i = 0; i < originalValues.size(); ++i) {
        diff[i] = originalValues[i] - convertedValues[i];
    }
    return diff;
}

std::vector<Float2> DiscreteCosineTransformation::convertToValueTuple(std::vector<float> values) {
    std::vector<Float2> tupleValues(values.size());
    for (int i = 0; i < values.size(); ++i) {
        tupleValues[i] = Float2(i, values[i]);
    }

    return tupleValues;
}

std::vector<Float2> DiscreteCosineTransformation::baseFunctions(int u, int samples, float step) {
    float m = samples / step;
    std::vector<Float2> functions(m);
    int cont = 0;
    float fu = 0;
    for (float x = 0; x < samples; x += step) {
        fu = cos(((2 * x + 1) * u * PI) / (2.0 * samples));
        functions[cont++] = Float2(x, fu);
    }

    return functions;
}


//Quantization factor as proposed in: https://en.wikipedia.org/wiki/Quantization_(signal_processing)
std::vector<float> DiscreteCosineTransformation::generateQuantizationVector(int samples, int quantizationFactor) {

    std::vector<float> quantizationVector(samples);
    for (int i = 0; i < samples; ++i) {
        quantizationVector[i] = quantizationFactor;
    }

    return quantizationVector;
}

std::vector<float>
DiscreteCosineTransformation::applyQuantization(std::vector<float> values, std::vector<float> quantizationVector,
                                                int quantizationFactor) {
    std::vector<float> quantizedValues(values.size());

    for (int i = 0; i < values.size(); ++i) {
        if (quantizationFactor == 0)
            quantizedValues[i] = values[i];
        else
            quantizedValues[i] = floor((values[i] / quantizationVector[i]) + (1 / 2.0));
    }

    return quantizedValues;
}


std::vector<float>
DiscreteCosineTransformation::applyInverseQuantization(std::vector<float> values, std::vector<float> quantizationVector,
                                                       int quantizationFactor) {
    std::vector<float> quantizedValues(values.size());

    for (int i = 0; i < values.size(); ++i) {
        if (quantizationFactor == 0)
            quantizedValues[i] = values[i];
        else
            quantizedValues[i] = values[i] * quantizationVector[i];
    }

    return quantizedValues;
}

std::vector<int> DiscreteCosineTransformation::generateRandomValues(int samples) {

    srand(time(nullptr));
    std::vector<int> values(samples);
    for (int i = 0; i < samples; ++i) {
        values[i] = rand() % 255 - 128;
    }

    return values;
}