#include "DisplayPageTemperatureOnly.h"
#include "Logger.h"

DisplayPageTemperatureOnly::DisplayPageTemperatureOnly(DisplayManager *instanceOfDisplayManager) {
    display = instanceOfDisplayManager;
}

const char* DisplayPageTemperatureOnly::getPageName() {
    return "DisplayPageTemperatureOnly";
}

void DisplayPageTemperatureOnly::printScreen(unsigned int isrCounter, int offlineMode, const BrewData& b, const PidData& p, const WifiData& w, const MqttData& m) {

    // Show shot timer:
    if (displayShottimer()) {
        // Display was updated, end here
        return;
    }

    // Print the machine state
    if (displayMachineState()) {
        // Display was updated, end here
        return;
    }

    wifiData = w; // TODO: this is not good, you have to do it in every DisplayPage, don't you a member variable at all or force it via base ctor to be set
    mqttData = m; // TODO: this is not good, you have to do it in every DisplayPage, don't you a member variable at all or force it via base ctor to be set

    // If no specific machine state was printed, print default:
    display->clearBuffer();

    // draw (blinking) temp
    if (((fabs(p.input - p.setpoint) < blinkingtempoffset && blinkingtemp == 0) || (fabs(p.input - p.setpoint) >= blinkingtempoffset && blinkingtemp == 1)) && !FEATURE_STATUS_LED) {
        if (isrCounter < 500) {
            if (p.input < 99.999) {
                display->setCursor(8, 22);
                display->setFont(FontType::fup35);
                display->print(p.input, 1);
                display->drawCircle(116, 27, 4);
            }
            else {
                display->setCursor(24, 22);
                display->setFont(FontType::fup35);
                display->print(p.input, 0);
                display->drawCircle(116, 27, 4);
            }
        }
    }
    else {
        if (p.input < 99.999) {
            display->setCursor(8, 22);
            display->setFont(FontType::fup35);
            display->print(p.input, 1);
            display->drawCircle(116, 27, 4);
        }
        else {
            display->setCursor(24, 22);
            display->setFont(FontType::fup35);
            display->print(p.input, 0);
            display->drawCircle(116, 27, 4);
        }
    }

    displayStatusbar(offlineMode);

    display->sendBuffer();
}
