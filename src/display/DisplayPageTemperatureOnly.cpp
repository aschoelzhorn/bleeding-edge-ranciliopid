#include "DisplayPageTemperatureOnly.h"
#include "Logger.h"

DisplayPageTemperatureOnly::DisplayPageTemperatureOnly(DisplayManager *instanceOfDisplayManager) {
    display = instanceOfDisplayManager;
}

const char* DisplayPageTemperatureOnly::getPageName() {
    return "DisplayPageTemperatureOnly";
}

void DisplayPageTemperatureOnly::printScreen(double temperature, double setpoint, unsigned int isrCounter, int offlineMode, const BrewData& b, const PidData& p) {

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

    // If no specific machine state was printed, print default:
    display->clearBuffer();

    // draw (blinking) temp
    if (((fabs(temperature - setpoint) < blinkingtempoffset && blinkingtemp == 0) || (fabs(temperature - setpoint) >= blinkingtempoffset && blinkingtemp == 1)) && !FEATURE_STATUS_LED) {
        if (isrCounter < 500) {
            if (temperature < 99.999) {
                display->setCursor(8, 22);
                display->setFont(FontType::fup35);
                display->print(temperature, 1);
                display->drawCircle(116, 27, 4);
            }
            else {
                display->setCursor(24, 22);
                display->setFont(FontType::fup35);
                display->print(temperature, 0);
                display->drawCircle(116, 27, 4);
            }
        }
    }
    else {
        if (temperature < 99.999) {
            display->setCursor(8, 22);
            display->setFont(FontType::fup35);
            display->print(temperature, 1);
            display->drawCircle(116, 27, 4);
        }
        else {
            display->setCursor(24, 22);
            display->setFont(FontType::fup35);
            display->print(temperature, 0);
            display->drawCircle(116, 27, 4);
        }
    }

    displayStatusbar(offlineMode);

    display->sendBuffer();
}
