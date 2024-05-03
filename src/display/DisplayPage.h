#pragma once

#include <Arduino.h>
#include "DisplayManager.h"
#include "ImageDictionary.h"

#include <DTOs/brewData.h>
#include <DTOs/pidData.h>
#include <DTOs/wifiData.h>
#include <DTOs/stateData.h>
#include <DTOs/mqttData.h>
#include <DTOs/machineData.h>

enum class DisplayPageType {
    TemperatureOnly,
    Minimal,
    Standard,
    Scale
};

class DisplayPage {
public:
    virtual void printScreen(const BrewData& b, const PidData& p, const WifiData& w, const MqttData& m, const StateData& s, const MachineData& md) = 0;
    virtual const char* getPageName() = 0;
    virtual void displayMessage(String text1, String text2, String text3, String text4, String text5, String text6);
    virtual void displayLogo(String displaymessagetext, String displaymessagetext2);

protected:
    void displayWaterIcon(int x, int y);
    void displayUptime(int x, int y, const char* format);
    void displayWiFiStatus(int x, int y, const WifiData& w);
    void displayMQTTStatus(int x, int y, MqttData& m);
    void displayThermometerOutline(int x, int y, double setpoint);
    void drawTemperaturebar(int x, int y, int heightRange, double temperature);
    void displayTemperature(int x, int y, double temperature);
    void displayBrewtime(int x, int y, double brewtime);
    void displayProgressbar(int value, int x, int y, int width);
    void displayStatusbar(int offlineMode);
    bool displayShottimer();
    bool displayMachineState();

    // TODO: rethink this
    WifiData wifiData;
    MqttData mqttData;
    StateData stateData;
    PidData pidData;
    BrewData brewData;
    MachineData machineData;

    DisplayManager *display;
    ImageDictionary images;
};
