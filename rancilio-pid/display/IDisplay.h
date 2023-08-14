#ifndef IDISPLAY_H
#define IDISPLAY_H

#include "../rancilio-enums.h"
#include "../userConfig.h"

class IDisplay {
public:
    // virtual void clearScreen() = 0;
    // virtual void showText(const char* text) = 0;
    // ... Add more virtual methods as needed ...
    virtual void displaymessage(State state, char* message1, char* message2) = 0;

    virtual bool screenSaverRunning();
    //virtual void displaymessage(State, char*, char*);
    virtual void displaymessage_helper(State, char*, char*);
    virtual void showScreenSaver();
    virtual void showMenu(char**, char**);
    virtual void showPowerOffCountdown(char*, char*);
    virtual void showSoftwareUpdate();
};

#endif // IDISPLAY_H