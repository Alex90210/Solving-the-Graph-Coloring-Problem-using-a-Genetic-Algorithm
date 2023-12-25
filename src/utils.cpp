#include "../include/utils.h"

void scale_values(std::vector<int>& values, double min, double max) {
    double currentMin = *std::min_element(values.begin(), values.end());
    double currentMax = *std::max_element(values.begin(), values.end());

    for (int& value : values) {
        value = min + (value - currentMin) * (max - min) / (currentMax - currentMin);
    }
}

void raise_to_power(std::vector<int>& values, double power) {
    for (int& value : values) {
        value = std::pow(value, power);
    }
}