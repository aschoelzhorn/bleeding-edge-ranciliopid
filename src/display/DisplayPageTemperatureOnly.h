#pragma once

#include <Arduino.h>
#include "DisplayPage.h"
#include <DTOs/brewData.h>

class DisplayPageTemperatureOnly : public DisplayPage {
public:
    DisplayPageTemperatureOnly(DisplayManager *instanceOfDisplayManager);

    void printScreen(unsigned int isrCounter, int offlineMode, const BrewData& b, const PidData& p, const WifiData& w, const MqttData& m) override;
    const char* getPageName() override;

private:
    // Define some Displayoptions
    int blinkingtemp = 1;           // 0: blinking near setpoint, 1: blinking far away from setpoint
    float blinkingtempoffset = 0.3; // offset for blinking
};
