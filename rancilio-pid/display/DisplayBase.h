#ifndef DISPLAYBASE_H
#define DISPLAYBASE_H

#include "userConfig.h"
const int Display = DISPLAY_HARDWARE;

#include "rancilio-pid.h"
#include "rancilio-enums.h"
#include "controls.h"
#include "icon_shared.h"
#if (ENABLE_BIG_STATUS_ICONS)
#include "icon_big.h"
#else
#include "icon.h"
#endif
#if (ICON_COLLECTION == 2)
#include "icon_winter.h"
#elif (ICON_COLLECTION == 1)
#include "icon_smiley.h"
#else
#include "icon_simple.h" // also used as placeholder for ICON_COLLECTION==3
#endif

class DisplayBase {
public:
    DisplayBase();
private:
    bool softwareUpdateCheck();
    bool menuCheck();
    char* outputSimpleState();
    void setDisplayTextState(State activeState, char* displaymessagetext, char* displaymessagetext2);

    const unsigned int powerOffCountDownStart = 300;
    const int brewReadyWaitPeriod = 300000;
    const int userActivityWaitPeriod = 180000;

    unsigned long previousMillisDisplay = 0; // initialisation at the end of init()
    const long intervalDisplay = 1000; // update for display
    bool image_flip = true;
    unsigned int enableScreenSaver = ENABLE_SCREEN_SAVER;
    bool screenSaverOn = false;
};

#endif // DISPLAYBASE_H
