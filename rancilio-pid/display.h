#ifndef _display_H
#define _display_H

#include "userConfig.h"
// const int Display = DISPLAY_HARDWARE;

#include <map>
#include "rancilio-pid.h"
#include "rancilio-enums.h"
#include "controls.h"
#include "display/status_images.h"

const int Display = DISPLAY_HARDWARE;

#if DISPLAY_HARDWARE == 4

#ifdef MACHINE_TYPE_GAGGIA
#include "display/icons/icon_gaggia_color.h"
#elif defined(MACHINE_TYPE_ECM)
#include "display/icons/icon_ecm_color.h"
#elif defined(MACHINE_TYPE_RANCILIO)
#include "display/icons/icon_rancilio_color.h"
#else
#include "display/icons/icon_generic_color_.h"
#endif
#include "display/icons/icon_shared_color.h"

#else

#ifdef MACHINE_TYPE_GAGGIA
#include "display/icons/icon_gaggia.h"
#elif defined(MACHINE_TYPE_ECM)
#include "display/icons/icon_ecm.h"
#elif defined(MACHINE_TYPE_RANCILIO)
#include "display/icons/icon_rancilio.h"
#else
#include "display/icons/icon_generic.h"
#endif

#include "display/icons/icon_shared.h"
#endif

#if (ENABLE_BIG_STATUS_ICONS)
#include "display/icons/icon_big.h"
#else
#include "display/icons/icon.h"
#endif
#if (ICON_COLLECTION == 2)
#include "display/icons/icon_winter.h"
#elif (ICON_COLLECTION == 1)
#include "display/icons/icon_smiley.h"
#else
#include "display/icons/icon_simple.h" // also used as placeholder for ICON_COLLECTION==3
#endif



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

//bool screenSaverRunning();
void displaymessage(State, char*, char*);
//void displaymessage_helper(State, char*, char*);
//void showScreenSaver();
//void showMenu(char**, char**);
//void showPowerOffCountdown(char*, char*);
//void showSoftwareUpdate();

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
extern const char* convertDefineToReadAbleVariable(char*);
extern float currentWeight;
extern unsigned int brewStatisticsAdditionalDisplayTime;
extern unsigned long brewStatisticsTimer;

#endif