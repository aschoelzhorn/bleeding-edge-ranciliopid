#pragma once

#include <brewEnums.h>

struct BrewData {
    int isBrewDetected;
    BrewState currBrewState;
    unsigned long timeBrewDetection;
    double brewtimesoftware;
    double timeBrewed;
    double totalBrewTime;
    double lastBrewTime;
    int brewSwitchState;
    float weightBrew;
};