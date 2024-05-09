#include "DisplayPageMinimal.h"
#include "languages.h"
#include <DTOs/brewData.h>
#include <DTOs/pidData.h>

DisplayPageMinimal::DisplayPageMinimal(DisplayManager *instanceOfDisplayManager) {
    display = instanceOfDisplayManager;
}

/**
 * @brief Return the name of the page / template
 */
const char* DisplayPageMinimal::getPageName() {
    return "DisplayPageMinimal";
}

/**
 * @brief Send data to display
 */
void DisplayPageMinimal::printScreen(const BrewData& b, const PidData& p, const WifiData& w, const MqttData& m, const StateData& s, const MachineData& md) {

    wifiData = w; // TODO: this is not good, you have to do it in every DisplayPage, don't use a member variable at all or force it via base ctor to be set
    mqttData = m; // TODO: this is not good, you have to do it in every DisplayPage, don't use a member variable at all or force it via base ctor to be set
    stateData = s; // TODO: this is not good, you have to do it in every DisplayPage, don't use a member variable at all or force it via base ctor to be set
    pidData = p; // TODO: this is not good, you have to do it in every DisplayPage, don't use a member variable at all or force it via base ctor to be set
    brewData = b; // TODO: this is not good, you have to do it in every DisplayPage, don't use a member variable at all or force it via base ctor to be set 
    machineData = md; // TODO: this is not good, you have to do it in every DisplayPage, don't use a member variable at all or force it via base ctor to be set     

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

    displayStatusbar(s.offlineMode);

    int numDecimalsInput = 1;

    if (p.input > 99.999) {
        numDecimalsInput = 0;
    }

    int numDecimalsSetpoint = 1;

    if (p.setpoint > 99.999) {
        numDecimalsSetpoint = 0;
    }
    
    Viewport temp = display->getView(Area::Temperature);
    // Draw temp, blink if feature STATUS_LED is not enabled
    if ((fabs(p.input - p.setpoint) < 0.3) && !FEATURE_STATUS_LED) {
        if (s.isrCounter < 500) {
            // limit to 4 characters
            display->setCursor(2, 20);
            display->setFont(FontType::Big);
            display->print(p.input, numDecimalsInput);
            display->setFont(FontType::OpenIconicArrow2x);
            display->print(char(78));
            display->setCursor(78, 20);
            display->setFont(FontType::Big);
            display->print(p.setpoint, numDecimalsSetpoint);
        }
    }
    else {
        display->setCursor(2, 20);
        display->setFont(FontType::Big);
        display->print(p.input, numDecimalsInput);
        display->setFont(FontType::OpenIconicArrow2x);
        display->setCursor(56, 24);

        if (p.mode == 1) {
            display->print(char(74));
        }
        else {
            display->print(char(70));
        }

        display->setCursor(79, 20);
        display->setFont(FontType::Big);
        display->print(p.setpoint, numDecimalsSetpoint);
    }

    display->setFont(FontType::Normal);

    char brewString[20];
    if (b.isBrewDetected == 1 && b.currBrewState == BrewState::kBrewIdle) {
        const char* format = "BD: %.1f/%.0f";
        snprintf(brewString, sizeof(brewString), format, ((millis() - b.timeBrewDetection) / 1000), b.brewtimesoftware);
        display->printCentered(Area::BrewTime, (char*)brewString);
    }
    else {
        const char* format = "%s%.0f/%.0f";
        if (BREWCONTROL_TYPE == 0) {
            snprintf(brewString, sizeof(brewString), format, langstring_brew, (b.timeBrewed / 1000), b.brewtimesoftware);
        }
        else {
            snprintf(brewString, sizeof(brewString), format, langstring_brew, (b.timeBrewed / 1000), (b.totalBrewTime / 1000));
        }
        display->printCentered(Area::BrewTime, (char*)brewString);
    }

    // Show heater output in %
    Viewport pg = display->getView(Area::Progressbar);
    displayProgressbar(p.output / 10, pg.getUpperLeft().X + 15, pg.getUpperLeft().Y, 100);

    display->sendBuffer();
}
