#ifndef _display_H
#define _display_H

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

#ifdef ESP32
static State activeStateBuffer;
#endif
static char displaymessagetextBuffer[30];
static char displaymessagetext2Buffer[30];

#define LCDWidth 128 //display.width
#define LCDHeight 64 //display.height
//#define ALIGN_CENTER(t) ((LCDWidth - (display.getUTF8Width(t))) / 2)
#define ALIGN_CENTER(t) ((LCDWidth - 10) / 2)

extern unsigned long previousMillisDisplay; // initialisation at the end of init()
extern const long intervalDisplay; // update for display
extern bool image_flip;
extern unsigned int enableScreenSaver;
extern bool screenSaverOn;
const int brewReadyWaitPeriod = 300000;
const int userActivityWaitPeriod = 180000;

void prepare(void);
bool screenSaverRunning();
void displaymessage(State, char*, char*);
void displaymessage_helper(State, char*, char*);
void showScreenSaver();
void showMenu(char**, char**);
void showPowerOffCountdown(char*, char*);
void showSoftwareUpdate();

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
extern const char* convertDefineToReadAbleVariable(char*);
extern float currentWeight;
extern unsigned int brewStatisticsAdditionalDisplayTime;
extern unsigned long brewStatisticsTimer;

#endif