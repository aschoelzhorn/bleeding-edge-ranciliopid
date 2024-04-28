#ifndef DisplayPageMinimal_H
#define DisplayPageMinimal_H

#include <Arduino.h>
#include "DisplayPage.h"

class DisplayPageMinimal : public DisplayPage {
public:
    DisplayPageMinimal(DisplayManager *instanceOfDisplayManager);

    void printScreen(double temperature, double setpoint, unsigned int isrCounter, int offlineMode, const BrewData& b, const PidData& p) override;
    const char* getPageName() override;

private:
    // Define some Displayoptions
    int blinkingtemp = 1;           // 0: blinking near setpoint, 1: blinking far away from setpoint
    float blinkingtempoffset = 0.3; // offset for blinking
};

#endif