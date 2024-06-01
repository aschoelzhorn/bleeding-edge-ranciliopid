#pragma once

#include "IDisplayPage.h"

class DisplayPageColorBase : public IDisplayPage {
public:
    void displayMessage(String text1, String text2, String text3, String text4, String text5, String text6) override;
    void displayLogo(String displaymessagetext, String displaymessagetext2) override;

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

    void setStateData(const BrewData&, const PidData&, const WifiData&, const MqttData&, const StateData&, const MachineData&, const ScaleData&) override;

    // TODO: check which are really needed and if probably better moved to ech concrete implementation
    Viewport bootLogo;
    Viewport bootMessage;
    Viewport actionImage;
    Viewport statusIcons;
    Viewport profileIcon;
    Viewport temperature;
    Viewport statusMessage;
    Viewport softwareUpdate;

    Viewport statusbar;
    Viewport progressbar;
    Viewport brewTime;    
};
