#pragma once

#include <Arduino.h>

struct ScaleData {
    bool scaleFailure;
    float weightBrew;
    float weight;
    double weightSetpoint;
};