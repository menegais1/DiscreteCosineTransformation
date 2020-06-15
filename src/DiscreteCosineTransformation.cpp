//
// Created by menegais1 on 14/06/2020.
//

#include <cmath>
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
