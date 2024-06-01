/**
 * @file displayTemplateScale.h
 *
 * @brief Display template with brew scale
 *
 */

#include "DisplayPageScale.h"


DisplayPageScale::DisplayPageScale(DisplayManager *instanceOfDisplayManager) {
    display = instanceOfDisplayManager;
}

/**
 * @brief Return the name of the page / template
 */
const char* DisplayPageScale::getPageName() {
    return "DisplayPageScale";
}

void DisplayPageScale::initViews() {

}

/**
 * @brief Send data to display
 */
void DisplayPageScale::printScreen(const BrewData& b, const PidData& p, const WifiData& w, const MqttData& m, const StateData& s, const MachineData& md, const ScaleData& sd) {

    setStateData(b, p, w, m, s, md, sd);

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

    displayThermometerOutline(4, 62, p.setpoint);

    // Draw current temp in thermometer
    if (fabs(p.input - p.setpoint) < 0.3) {
        if (s.isrCounter < 500) {
            drawTemperaturebar(8, 50, 30, p.input);
        }
    }
    else {
        drawTemperaturebar(8, 50, 30, p.input);
    }

    display->setFont(FontType::Normal);

    display->setCursor(32, 16);
    display->print("T: ");
    display->print(p.input, 1);

    display->print("/");
    display->print(p.setpoint, 1);

    display->setCursor(32, 26);
    display->print("W: ");

    if (sd.scaleFailure) {
        display->print("fault");
    }
    else {
        if (md.state == MachineState::kBrew) {
            display->print(sd.weightBrew, 0);
        }
        else {
            display->print(sd.weight, 0);
        }

        display->print("/");
        display->print(sd.weightSetpoint, 0);
        display->print(" (");
        display->print(sd.weightBrew, 1);
        display->print(")");
    }

    // Brew
    display->setCursor(32, 36);
    display->print("t: ");
    display->print(b.timeBrewed / 1000, 0);
    display->print("/");

    if (BREWCONTROL_TYPE == 0) {
        display->print(b.brewtimesoftware, 0);
    }
    else {
        display->print(b.totalBrewTime / 1000, 1);
    }

#if (FEATURE_PRESSURESENSOR == 1)
    display->setCursor(32, 46);
    display->print("P: ");
    display->print(s.inputPressure, 1);
#endif

    // Show heater output in %
    displayProgressbar(p.output / 10, 30, 60, 98);

    display->sendBuffer();
}
