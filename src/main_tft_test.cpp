/**
 * @file main.cpp
 *
 * @brief Main sketch
 *
 * @version 4.0.0 Master
 */

// Firmware version
#define FW_VERSION    4
#define FW_SUBVERSION 0
#define FW_HOTFIX     0
#define FW_BRANCH     "MASTER"

// STL includes
#include <map>

// Libraries & Dependencies
#include "display/DisplayManager.h"
#include "display/DisplayPageManager.h"
#include "display/templates/IDisplayPage.h"
#include <os.h>

// // Utilities:
// #include "utils/Timer.h"

// Includes
#include "languages.h"       // for language translation
#include "machineStateEnum.h"

// Hardware classes
#include "hardware/pinmapping.h"

// User configuration & defaults
#include "userConfig.h" // needs to be configured by the user

// DTOs
#include "DTOs/brewData.h"
#include "DTOs/pidData.h"
#include "DTOs/wifiData.h"
#include "DTOs/mqttData.h"
#include "DTOs/machineData.h"
#include "DTOs/stateData.h"
#include "DTOs/scaleData.h"

hw_timer_t* timer = NULL;

MACHINE machine = (enum MACHINE)MACHINEID;

#define HIGH_ACCURACY

MachineState machineState = kInit;
MachineState lastmachinestate = kInit;
int lastmachinestatepid = -1;

// Definitions below must be changed in the userConfig.h file
int connectmode = CONNECTMODE;

int offlineMode = 0;
const boolean ota = OTA;

// Display
DisplayManager display;
DisplayPageManager displayPageManager(&display);

// WiFi
uint8_t wifiCredentialsSaved = 0;
const unsigned long wifiConnectionDelay = WIFICONNECTIONDELAY;
const unsigned int maxWifiReconnects = MAXWIFIRECONNECTS;
const char* hostname = HOSTNAME;
const char* pass = PASS;
unsigned long lastWifiConnectionAttempt = millis();
unsigned int wifiReconnects = 0; // actual number of reconnects

// OTA
const char* OTApass = OTAPASS;

// copy of default default parameters
#define SETPOINT                  93     // brew temperature setpoint
#define TEMPOFFSET                0      // brew temperature setpoint
#define STEAMSETPOINT             120    // steam temperature setpoint
#define SCALE_CALIBRATION_FACTOR  1.00   // Raw data is divided by this value to convert to readable data
#define SCALE2_CALIBRATION_FACTOR 1.00   // Raw data is divided by this value to convert to readable data
#define SCALE_KNOWN_WEIGHT        267.00 // Calibration weight for scale (weight of the tray)
#define AGGKP                     67     // PID Kp (regular phase)
#define AGGTN                     52     // PID Tn (regular phase)
#define AGGTV                     11.5   // PID Tv (regular phase)
#define AGGIMAX                   55     // PID Integrator Max (regular phase)
#define STARTKP                   45     // PID Kp (coldstart phase)
#define STARTTN                   130    // PID Tn (coldstart phase)
#define STEAMKP                   150    // PID kp (steam phase)
#define AGGBKP                    50     // PID Kp (brew detection phase)
#define AGGBTN                    0      // PID Tn (brew detection phase)
#define AGGBTV                    20     // PID Tv (brew detection phase)
#define BREW_TIME                 25     // brew time in seconds (only used if pump is being controlled)
#define BREW_SW_TIME              25     // keep brew PID params for this many seconds after detection (only for software BD)
#define BREW_PID_DELAY            10     // delay until enabling PID controller during brew (no heating during this time)
#define BD_SENSITIVITY            120    // brew detection sensitivity, be careful: if too low, then there is the risk of wrong brew detection and rising temperature
#define PRE_INFUSION_TIME         2      // pre-infusion time in seconds
#define PRE_INFUSION_PAUSE_TIME   5      // pre-infusion pause time in seconds
#define SCALE_WEIGHTSETPOINT      30     // Target weight in grams
#define WIFI_CREDENTIALS_SAVED    0      // Flag if wifi setup is done. 0: not set up, 1: credentials set up via wifi manager
#define STANDBY_MODE_ON           0      // Standby mode off by default
#define STANDBY_MODE_TIME         30     // Time in minutes until the heater is turned off

#define PID_KP_START_MIN       0
#define PID_KP_START_MAX       999
#define PID_TN_START_MIN       0
#define PID_TN_START_MAX       999
#define PID_KP_REGULAR_MIN     0
#define PID_KP_REGULAR_MAX     999
#define PID_TN_REGULAR_MIN     0
#define PID_TN_REGULAR_MAX     999
#define PID_TV_REGULAR_MIN     0
#define PID_TV_REGULAR_MAX     999
#define PID_I_MAX_REGULAR_MIN  0
#define PID_I_MAX_REGULAR_MAX  999
#define PID_KP_BD_MIN          0
#define PID_KP_BD_MAX          999
#define PID_TN_BD_MIN          0
#define PID_TN_BD_MAX          999
#define PID_TV_BD_MIN          0
#define PID_TV_BD_MAX          999
#define BREW_SETPOINT_MIN      20
#define BREW_SETPOINT_MAX      110
#define STEAM_SETPOINT_MIN     100
#define STEAM_SETPOINT_MAX     140
#define BREW_TEMP_OFFSET_MIN   0
#define BREW_TEMP_OFFSET_MAX   20
#define BREW_TEMP_TIME_MIN     1
#define BREW_TEMP_TIME_MAX     180
#define BREW_TIME_MIN          1
#define BREW_TIME_MAX          180
#define BREW_PID_DELAY_MIN     0
#define BREW_PID_DELAY_MAX     60
#define BREW_SW_TIME_MIN       1
#define BREW_SW_TIME_MAX       180
#define BD_THRESHOLD_MIN       0
#define BD_THRESHOLD_MAX       999
#define PRE_INFUSION_TIME_MIN  0
#define PRE_INFUSION_TIME_MAX  60
#define PRE_INFUSION_PAUSE_MIN 0
#define PRE_INFUSION_PAUSE_MAX 60
#define WEIGHTSETPOINT_MIN     0
#define WEIGHTSETPOINT_MAX     500
#define PID_KP_STEAM_MIN       0
#define PID_KP_STEAM_MAX       500
#define STANDBY_MODE_TIME_MIN  30
#define STANDBY_MODE_TIME_MAX  120


// system parameters
uint8_t pidON = 0; // 1 = control loop in closed loop
double brewSetpoint = SETPOINT;
double brewTempOffset = TEMPOFFSET;
double setpoint = brewSetpoint;
double steamSetpoint = STEAMSETPOINT;
float scaleCalibration = SCALE_CALIBRATION_FACTOR;
float scale2Calibration = SCALE_CALIBRATION_FACTOR;
float scaleKnownWeight = SCALE_KNOWN_WEIGHT;
uint8_t usePonM = 0; // 1 = use PonM for cold start PID, 0 = use normal PID for cold start
double steamKp = STEAMKP;
double startKp = STARTKP;
double startTn = STARTTN;
double aggKp = AGGKP;
double aggTn = AGGTN;
double aggTv = AGGTV;
double aggIMax = AGGIMAX;
double brewTime = BREW_TIME;                       // brewtime in s
double preinfusion = PRE_INFUSION_TIME;            // preinfusion time in s
double preinfusionPause = PRE_INFUSION_PAUSE_TIME; // preinfusion pause time in s
double weightSetpoint = SCALE_WEIGHTSETPOINT;

// PID - values for offline brew detection
uint8_t useBDPID = 0;
double aggbKp = AGGBKP;
double aggbTn = AGGBTN;
double aggbTv = AGGBTV;

double aggbKi = 0;

double aggbKd = aggbTv * aggbKp;
double brewtimesoftware = BREW_SW_TIME;  // use userConfig time until disabling BD PID
double brewSensitivity = BD_SENSITIVITY; // use userConfig brew detection sensitivity
double brewPIDDelay = BREW_PID_DELAY;    // use userConfig brew detection PID delay

boolean brewDetected = 0;

int backflushState = 10;

// Water sensor
boolean waterFull = true;

// Moving average for software brew detection
unsigned long timeBrewDetection = 0;
int isBrewDetected = 0; // flag is set if brew was detected

// PID controller
unsigned long previousMillistemp; // initialisation at the end of init()

double setpointTemp;
double previousInput = 0;

// Variables to hold PID values (Temp input, Heater output)
double temperature, pidOutput;
int steamON = 0;
int steamFirstON = 0;

double startKi = 0;
double aggKi = 0;
double aggKd = aggTv * aggKp;

//#include "brewHandler.h"

int currentPageIndex = DISPLAYTEMPLATE;
int prevPageIndex = currentPageIndex;

DisplayPageType templateType = static_cast<DisplayPageType>(currentPageIndex);
IDisplayPage *page = displayPageManager.getPage(templateType);

int brewSwitchState = kBrewSwitchIdle;
double totalBrewTime = 0;        // total brewtime set in software
double timeBrewed = 0;           // total brewed time
double lastBrewTime = 0;
unsigned long startingTime = 0;  // start time of brew

void printScreen() {

    BrewData brewData;
    brewData.brewtimesoftware = brewtimesoftware;
    brewData.currBrewState = BrewState::kBrewFinished;
    brewData.isBrewDetected = isBrewDetected;
    brewData.timeBrewDetection = timeBrewDetection;
    brewData.timeBrewed = timeBrewed;
    brewData.totalBrewTime = totalBrewTime;
    brewData.brewSwitchState = brewSwitchState;
    brewData.lastBrewTime = lastBrewTime;
#if FEATURE_SCALE == 1    
    brewData.weightBrew = weightBrew;
#endif

    PidData pidData;
    pidData.mode = 1;
    pidData.kd = 12;
    pidData.ki = 13;
    pidData.kp = 14;
    pidData.input = temperature;
    pidData.output = pidOutput;
    pidData.setpoint = setpoint;

    WifiData wifiData;
    wifiData.isConnected = true;
    wifiData.signalStrength = 0; //0-4
    wifiData.reconnects = wifiReconnects;

    MqttData mqttData;
    mqttData.isConnected = true;

    StateData stateData;
    stateData.isrCounter = 0;
    stateData.offlineMode = offlineMode;
    stateData.waterFull = waterFull;
    stateData.flushCycles = 0;
    stateData.maxflushCycles = 0;
    stateData.backflushState = backflushState;
#if (FEATURE_PRESSURESENSOR == 1)    
    stateData.inputPressure = inputPressure;
#endif    

    MachineData machineData;
    machineData.state = machineState;

    ScaleData scaleData;
#if FEATURE_SCALE == 1
    scaleData.scaleFailure = SCALE_CALIBRATION_FACTOR;
    scaleData.weight = weight;
    scaleData.weightBrew = weightBrew;
    scaleData.weightSetpoint = weightSetpoint;
#else
    scaleData.scaleFailure = false;
    scaleData.weight = 0;
    scaleData.weightBrew = 0;
    scaleData.weightSetpoint = weightSetpoint;
#endif

    // page can be change from web (no ui, just by url)
    if (currentPageIndex != prevPageIndex) {
        //LOGF(DEBUG, "CHANGE PAGE");
        //LOGF(DEBUG, "old page name: %s", page->getPageName());
        page = displayPageManager.getPage(static_cast<DisplayPageType>(currentPageIndex));
        prevPageIndex = currentPageIndex;
        //LOGF(DEBUG, "new page name: %s", page->getPageName());
    }

    page->printScreen(brewData, pidData, wifiData, mqttData, stateData, machineData, scaleData);
}

void setDisplayIndex(int index) {
    currentPageIndex = index;
}

uint32_t updateTime = 0;       // time for next update
#define LOOP_PERIOD 100 // Display updates every 100 ms

void setup() {
    // Start serial console
    Serial.begin(115200);
    Serial.println("Page name: ");Serial.println(page->getPageName());
    display.init(DISPLAYROTATE);
    page->displayLogo(String("Version "), String("4.0.0.0"));
    temperature = 56;
    temperature -= brewTempOffset;
    delay(3000);

    updateTime = millis(); // Next update time
    display.clearBuffer();

    Viewport statusbar = display.getView(Area::Statusbar);

    Serial.println(statusbar.getDebugString());
}



void loop() {
  if (updateTime <= millis()) {
    updateTime = millis() + LOOP_PERIOD;
    printScreen();
  }
 
}
