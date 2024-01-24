#ifndef _display_H
#define _display_H

#include "userConfig.h"
const int Display = DISPLAY_HARDWARE;

#include <map>
#include "rancilio-pid.h"
#include "rancilio-enums.h"
#include "controls.h"

#include "display/ImageDictionary.h"

#ifdef ESP32
static State activeStateBuffer;
#endif
static char displaymessagetextBuffer[30];
static char displaymessagetext2Buffer[30];

extern unsigned long previousMillisDisplay; // initialisation at the end of init()
extern const long intervalDisplay; // update for display
extern bool image_flip;
extern unsigned int enableScreenSaver;
extern bool screenSaverOn;
const int brewReadyWaitPeriod = 300000;
const int userActivityWaitPeriod = 180000;

void InitDisplay();

void updateDisplay(State, char*, char*);

void showBootLogo();
void hideBootLogo();

void displayMessageCentered(char*, uint16_t y);
void showBootMessage(char*);
void showBootMessage(char*, char*);
void hideBootMessage();

void showStatusMessage(char*);
void showStatusMessage(char*, char*);
void hideStatusMessage();

void clearDisplay();

extern bool brewReady;
extern unsigned long lastBrewReady;
extern int sleeping;
extern unsigned long userActivity;
extern State activeState;
extern float steamReadyTemp;
extern float Input;
extern int pidON;
extern int steaming;
extern unsigned long totalBrewTime;
extern const int OnlyPID;
extern unsigned int profile;
extern float* activeBrewtime;
extern float* activePreinfusion;
extern float* activePreinfusionPause;
extern unsigned int* activeBrewTimeEndDetection;
extern float* activeScaleSensorWeightSetPoint;
extern unsigned long brewTimer;
extern bool isWifiWorking();
extern bool isBlynkWorking();
extern bool isMqttWorking();
extern int brewing;
extern unsigned long lastBrewEnd;
extern unsigned int powerOffTimer;
extern unsigned int menuPosition;
extern unsigned long previousTimerMenuCheck;
extern const unsigned int menuOffTimer;
extern menuMap* menuConfig;
extern float menuValue;
extern const char* convertDefineToReadableVariable(char*);
extern float currentWeight;
extern unsigned int brewStatisticsAdditionalDisplayTime;
extern unsigned long brewStatisticsTimer;

#endif