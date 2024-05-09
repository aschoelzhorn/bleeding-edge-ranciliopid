#pragma once

#include <Arduino.h>
#include "DisplayPageColorBase.h"

class DisplayPageColorMinimal : public DisplayPageColorBase {
public:
    DisplayPageColorMinimal(DisplayManager *instanceOfDisplayManager);

    void printScreen(const BrewData& b, const PidData& p, const WifiData& w, const MqttData& m, const StateData& s, const MachineData& md) override;
    const char* getPageName() override;
};
