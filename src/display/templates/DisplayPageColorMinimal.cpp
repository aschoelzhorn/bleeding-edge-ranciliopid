#include "DisplayPageColorMinimal.h"
#include "Logger.h"
#include "languages.h"

DisplayPageColorMinimal::DisplayPageColorMinimal(DisplayManager *instanceOfDisplayManager) {
    display = instanceOfDisplayManager;
}

const char* DisplayPageColorMinimal::getPageName() {
    return "DisplayPageColorMinimal";
}


/**
 * @brief Send data to display
 */
void DisplayPageColorMinimal::printScreen(const BrewData& b, const PidData& p, const WifiData& w, const MqttData& m, const StateData& s, const MachineData& md, const ScaleData& sd) {

    setStateData(b, p, w, m, s, md, sd);   

    display->clearBuffer();
    display->setFont(FontType::Big); // set font

    // if (p.input < 99.999) {
    //     display->setCursor(8, 22);
    //     display->print(p.input, 1);
    //     display->drawCircle(116, 27, 4);
    // }
    // else {
    //     display->setCursor(24, 22);
    //     display->print(p.input, 0);
    //     display->drawCircle(116, 27, 4);
    // }


    int numDecimalsInput = 1;
    if (p.input > 99.999) {
        numDecimalsInput = 0;
    }

    int numDecimalsSetpoint = 1;

    if (p.setpoint > 99.999) {
        numDecimalsSetpoint = 0;
    }

    // limit to 4 characters
    display->setCursor(8, 22);
    display->print(p.input, numDecimalsInput);
    display->drawCircle(80, 27, 4);
    display->setCursor(90, 22);
    display->print("-->");
    display->setCursor(130, 22);
    display->print(p.setpoint, numDecimalsSetpoint);
    display->drawCircle(210, 27, 4);
 

    display->sendBuffer();
}
