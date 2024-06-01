#include "DisplayPageColor.h"
#include "languages.h"

DisplayPageColor::DisplayPageColor(DisplayManager *instanceOfDisplayManager) {
    display = instanceOfDisplayManager;
}

const char* DisplayPageColor::getPageName() {
    return "DisplayPageColor";
}

void DisplayPageColor::initViews() {
    // we could expose those 2 through the baseclass
    int displayWidth = 240;//display->getWidth();
    int displayHeight = 240;//display->getHeight();

    int margin = 5;
    int ccLogoHeight = 180;
    int statusIconHeight = 56;
    int statusIconWidth = 56;

    int iconHeight  = 45;

    int numberOfStatusIcons = 3;

    Point upperLeft = Point(0, 0);

    bootLogo = Viewport(upperLeft, displayWidth, ccLogoHeight);
    bootMessage = Viewport(0, bootLogo.getLowerLeft().Y + margin, displayWidth, displayHeight - bootLogo.getHeight() - margin);

    statusbar = Viewport(0, displayHeight - statusIconHeight, displayWidth, statusIconHeight);
    header = Viewport(0, 0, displayWidth, 20);


    // TOP: header with uptime and IP
    
    // actionImage = Viewport(upperLeft, displayWidth / 2, (displayHeight / 4));
    // temperature = Viewport(displayWidth / 2, upperLeft.Y, displayWidth / 2, (displayHeight / 2));

    // statusMessage = Viewport(0, actionImage.getHeight()*2 + margin, displayWidth, displayHeight - actionImage.getHeight()*2 - margin - statusIconHeight);
    // statusIcons = Viewport(Point(0, displayHeight - statusIconHeight), statusIconWidth * numberOfStatusIcons, statusIconHeight);
    // profileIcon = Viewport(Point(displayWidth - statusIconWidth, displayHeight - statusIconHeight), statusIconWidth, statusIconHeight);

    // softwareUpdate = Viewport(upperLeft, displayWidth, displayHeight); // fullscreen

    areaMap = {
        {Area::BootLogo, this->bootLogo},
        {Area::BootMessage, this->bootMessage},
        {Area::Statusbar, this->statusbar},
        {Area::Header, this->header},
    };

    display->setAreaMap(areaMap);
}


void DisplayPageColor::displayHeader() {
    const char* format = "%02luh %02lum";
    displayUptime(statusbar.getUpperLeft().X, statusbar.getUpperLeft().Y, format); // todo: could be improved, x not need, we used printRightAligned in displayUptime

    display->setFont(FontType::Normal);
    display->drawStr(statusbar.getUpperLeft().X, statusbar.getUpperLeft().Y, "192.168.123.123");
}

/**
 * @brief Send data to display
 */
void DisplayPageColor::printScreen(const BrewData& b, const PidData& p, const WifiData& w, const MqttData& m, const StateData& s, const MachineData& md, const ScaleData& sd) {

    setStateData(b, p, w, m, s, md, sd);    

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

    //display->clearBuffer();
    display->setFont(FontType::Normal); // set font

    displayHeader();
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

    //display->sendBuffer();
}
