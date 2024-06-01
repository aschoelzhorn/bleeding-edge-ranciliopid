#pragma once

#include <Arduino.h>
#include "../DisplayManager.h"
#include "../ImageDictionary.h"

#include "DisplayPageTypeEnum.h"

#include <DTOs/brewData.h>
#include <DTOs/pidData.h>
#include <DTOs/wifiData.h>
#include <DTOs/stateData.h>
#include <DTOs/mqttData.h>
#include <DTOs/machineData.h>
#include "DTOs/scaleData.h"

class IDisplayPage {
public:
    virtual void printScreen(const BrewData& b, const PidData& p, const WifiData& w, const MqttData& m, const StateData& s, const MachineData& md, const ScaleData& sd) = 0;
    virtual const char* getPageName() = 0;
    virtual void displayMessage(String text1, String text2, String text3, String text4, String text5, String text6) = 0;
    virtual void displayLogo(String displaymessagetext, String displaymessagetext2) = 0;

    virtual void initViews() = 0;
protected:
    virtual void setStateData(const BrewData&, const PidData&, const WifiData&, const MqttData&, const StateData&, const MachineData&, const ScaleData&) = 0;

    WifiData wifiData;
    MqttData mqttData;
    StateData stateData;
    PidData pidData;
    BrewData brewData;
    MachineData machineData;
    ScaleData scaleData;

    DisplayManager *display;
    ImageDictionary images;

    std::map<Area, Viewport> areaMap;
};
