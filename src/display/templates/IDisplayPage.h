#pragma once

#include <Arduino.h>
#include "../DisplayManager.h"
#include "../ImageDictionary.h"

#include <DTOs/brewData.h>
#include <DTOs/pidData.h>
#include <DTOs/wifiData.h>
#include <DTOs/stateData.h>
#include <DTOs/mqttData.h>
#include <DTOs/machineData.h>

enum class DisplayPageType {
    Undefined = 0,
    Standard = 1,
    Minimal = 2,
    TemperatureOnly = 3,
    Scale = 4, 
    Rotated = 20,
    Color = 100,
    ColorMinimal = 101
};

class IDisplayPage {
public:
    virtual void printScreen(const BrewData& b, const PidData& p, const WifiData& w, const MqttData& m, const StateData& s, const MachineData& md) = 0;
    virtual const char* getPageName() = 0;
    virtual void displayMessage(String text1, String text2, String text3, String text4, String text5, String text6) = 0;
    virtual void displayLogo(String displaymessagetext, String displaymessagetext2) = 0;

//protected:
    WifiData wifiData;
    MqttData mqttData;
    StateData stateData;
    PidData pidData;
    BrewData brewData;
    MachineData machineData;

    DisplayManager *display;
    ImageDictionary images;
};
