#pragma once

#include <Arduino.h>
#include "DisplayPageBase.h"

class DisplayPageMinimal : public DisplayPageBase {
public:
    DisplayPageMinimal(DisplayManager *instanceOfDisplayManager);

    void printScreen(const BrewData& b, const PidData& p, const WifiData& w, const MqttData& m, const StateData& s, const MachineData& md, const ScaleData& sd) override;
    const char* getPageName() override;

private:
    // Define some Displayoptions
    int blinkingtemp = 1;           // 0: blinking near setpoint, 1: blinking far away from setpoint
    float blinkingtempoffset = 0.3; // offset for blinking
};
