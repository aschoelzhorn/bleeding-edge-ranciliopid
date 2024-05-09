#include "DisplayPageColor.h"
#include "Logger.h"
#include "languages.h"

DisplayPageColor::DisplayPageColor(DisplayManager *instanceOfDisplayManager) {
    display = instanceOfDisplayManager;
}

const char* DisplayPageColor::getPageName() {
    return "DisplayPageColor";
}


/**
 * @brief Send data to display
 */
void DisplayPageColor::printScreen(const BrewData& b, const PidData& p, const WifiData& w, const MqttData& m, const StateData& s, const MachineData& md) {

    wifiData = w; // TODO: this is not good, you have to do it in every DisplayPage, don't use a member variable at all or force it via base ctor to be set
    mqttData = m; // TODO: this is not good, you have to do it in every DisplayPage, don't use a member variable at all or force it via base ctor to be set
    stateData = s; // TODO: this is not good, you have to do it in every DisplayPage, don't use a member variable at all or force it via base ctor to be set
    pidData = p; // TODO: this is not good, you have to do it in every DisplayPage, don't use a member variable at all or force it via base ctor to be set
    brewData = b; // TODO: this is not good, you have to do it in every DisplayPage, don't use a member variable at all or force it via base ctor to be set 
    machineData = md; // TODO: this is not good, you have to do it in every DisplayPage, don't use a member variable at all or force it via base ctor to be set     

    // // Show shot timer:
    // if (displayShottimer()) {
    //     // Display was updated, end here
    //     return;
    // }

    // // Print the machine state
    // if (displayMachineState()) {
    //     // Display was updated, end here
    //     return;
    // }

    // If no specific machine state was printed, print default:

    display->clearBuffer();
    display->setFont(FontType::Normal); // set font

    displayStatusbar(s.offlineMode);

    // display->setCursor(35, 16);
    // display->print(langstring_current_temp);
    // display->setCursor(84, 16);
    // display->print(p.input, 1);
    // display->setCursor(114, 16);
    // display->print((char)176);
    // display->print("C");
    // display->setCursor(35, 26);
    // display->print(langstring_set_temp);
    // display->setCursor(84, 26);
    // display->print(p.setpoint, 1);
    // display->setCursor(114, 26);
    // display->print((char)176);
    // display->print("C");

    // displayThermometerOutline(4, 62, p.setpoint);

    // // Draw current temp in thermometer
    // if (fabs(p.input - p.setpoint) < 0.3) {
    //     if (s.isrCounter < 500) {
    //         drawTemperaturebar(8, 50, 30, p.input);
    //     }
    // }
    // else {
    //     drawTemperaturebar(8, 50, 30, p.input);
    // }

    // // Brew time
    // display->setCursor(35, 36);

    // // Shot timer shown if machine is brewing and after the brew
    // if (md.state == MachineState::kBrew || md.state == MachineState::kShotTimerAfterBrew) {
    //     display->print(langstring_brew);
    //     display->setCursor(84, 36);
    //     display->print(b.timeBrewed / 1000, 0);
    //     display->print("/");

    //     if (BREWCONTROL_TYPE == 0) {
    //         display->print(b.brewtimesoftware, 0);
    //     }
    //     else {
    //         display->print(b.totalBrewTime / 1000, 1);
    //     }
    // }

    // // PID values over heat bar
    // display->setCursor(38, 47);

    // display->print(p.kp, 0);
    // display->print("|");

    // if (p.ki != 0) {
    //     display->print(p.kp / p.ki, 0);
    // }
    // else {
    //     display->print("0");
    // }

    // display->print("|");
    // display->print(p.kd / p.kp, 0);
    // display->setCursor(96, 47);

    // if (p.output < 99) {
    //     display->print(p.output / 10, 1);
    // }
    // else {
    //     display->print(p.output / 10, 0);
    // }

    // display->print("%");

    // // Show heater output in %
    // displayProgressbar(p.output / 10, 30, 60, 98);

    display->sendBuffer();
}
