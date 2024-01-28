/***********************************
 *  DISPLAY
 ***********************************/
#include <float.h>
#include "display.h"
#include "rancilio-debug.h"
#include "rancilio-helper.h"
#include "rancilio-network.h"

#include "display/ImageDictionary.h"

#include "display/DisplayManager.h"
extern DisplayManager display;  // declare the extern DisplayManager object to use the same instance everywhere

#include "display/DisplayHelper.h"
DisplayHelper displayHelper;

unsigned long previousMillisDisplay = 0; // initialisation at the end of init()
const long intervalDisplay = 1000; // update for display
bool image_flip = true;
unsigned int enableScreenSaver = ENABLE_SCREEN_SAVER;
bool screenSaverOn = false;
const unsigned int powerOffCountDownStart = 300;

ImageDictionary images;

char displayMessageLine1Cache[21] = "\0";
char displayMessageLine2Cache[21] = "\0";

bool softwareUpdateCheck() {
  return activeState == State::SoftwareUpdate;
}

bool screenSaverCheck() {
  if ((enableScreenSaver && brewReady && (millis() >= lastBrewReady + brewReadyWaitPeriod) && (millis() >= userActivity + userActivityWaitPeriod)) || sleeping) {
    menuPosition = 0;
    return true;
  } else {
    if (screenSaverOn) {
      display.setPowerSave(0);
      screenSaverOn = false;
    }
    return false;
  }
}

bool menuCheck() {
  if (menuPosition != 0 && (millis() <= previousTimerMenuCheck + menuOffTimer) ) {
    return true;
  } else {
    menuPosition = 0;
    return false;
  }
}

char* outputSimpleState() {
  switch (activeState) {
    case State::SteamMode: {
      return (char*)"Steaming";
    }
    case State::CleanMode: {
      return (char*)"Cleaning";
    }
    case State::SleepMode: {
      return (char*)"Sleeping";
    }
    default: {}
  }
  if (!pidON) { return (char*)"Turned off"; }
  if (brewReady) { return (char*)"Ready"; }
  return (char*)""; //"Please wait";
}

void setDisplayTextState(State activeState, char* displaymessagetext, char* displaymessagetext2) {
#if (DISPLAY_TEXT_STATE == 1)
  if (menuPosition != 0) return;
  if (strlen(displaymessagetext) > 0 || strlen(displaymessagetext2) > 0 || screenSaverOn || activeState == State::BrewDetected) { // dont show state in certain situations
    snprintf((char*)displaymessagetextBuffer, sizeof(displaymessagetextBuffer), "%s", displaymessagetext);
    snprintf((char*)displaymessagetext2Buffer, sizeof(displaymessagetext2Buffer), "%s", displaymessagetext2);
  } else {
    snprintf((char*)displaymessagetextBuffer, sizeof(displaymessagetextBuffer), "%s", displaymessagetext);
    snprintf((char*)displaymessagetext2Buffer, sizeof(displaymessagetext2Buffer), "%s", outputSimpleState());
  }
#else
  snprintf((char*)displaymessagetextBuffer, sizeof(displaymessagetextBuffer), "%s", displaymessagetext);
  snprintf((char*)displaymessagetext2Buffer, sizeof(displaymessagetext2Buffer), "%s", displaymessagetext2);
#endif
}

#ifdef ESP32
void updateDisplay_esp32_task(void* activeStateParam) {
  delay(100);
  for (;;) {
    // unsigned long cur_micros_display = micros();
    displaymessage_helper(activeStateBuffer, displaymessagetextBuffer, displaymessagetext2Buffer);
    // DEBUG_print("inside updateDisplay() done =%lu\n", micros()-cur_micros_display);
    vTaskDelay(intervalDisplay / portTICK_PERIOD_MS);
  }
  vTaskDelete(NULL);
}
#endif

void updateDisplay(State activeState, char* displaymessagetext, char* displaymessagetext2) {
  if (Display > 0) {
    static int only_once = 0;
#ifdef ESP32
    //DEBUG_print("activeState=%d | %s | %s\n", activeState, displaymessagetext, displaymessagetext2);
    if ((millis() >= previousMillisDisplay + intervalDisplay) || only_once == 0) {
      previousMillisDisplay = millis();
      activeStateBuffer = activeState;
      setDisplayTextState(activeStateBuffer, displaymessagetext, displaymessagetext2);
    }
    if (only_once == 0) {
      only_once = 1;
      xTaskCreatePinnedToCore(updateDisplay_esp32_task, /* Task function. */
          "updateDisplay", /* name of task. */
          2000, /* Stack size of task */
          (void*)&activeState, /* parameter of the task */
          6, /* priority of the task */
          NULL, /* Task handle to keep track of created task */
          0); /* pin task to core 1 */
    }
#else
    if (only_once == 0) {
      only_once = 1;
    }
    if ((millis() >= previousMillisDisplay + intervalDisplay) || previousMillisDisplay == 0) {
      previousMillisDisplay = millis();
      setDisplayTextState(activeState, displaymessagetext, displaymessagetext2);
      displaymessage_helper(activeState, displaymessagetextBuffer, displaymessagetext2Buffer);
    }
#endif
  }
}


void showImage(StatusImage image, bool flip) { 
  if (displayHelper.getCurrentActionImage(image_flip) == image) {
    return;
  }

  display.clearView(Area::ActionImage);
  if (image_flip) {
    display.drawImageCentered(Area::ActionImage, icon_width, icon_height, images.getImage(image));
  } else {
    display.drawImageCentered(Area::ActionImage, icon_width, icon_height, images.getImageRotated(image));
  }
  displayHelper.setCurrentActionImage(image, image_flip);
}


void showTemperatures(float t1, float t2, bool steaming) {
  display.printTemperatures(t1, t2, steaming);
}

void showBrewingInfo() {
  totalBrewTime = ( (OnlyPID || BREWTIME_TIMER == 0 )? *activeBrewTime : *activePreinfusion + *activePreinfusionPause + *activeBrewTime) * 1000;
  display.printBrewingInfo(totalBrewTime, brewTimer, *activeBrewTimeEndDetection, SCALE_SENSOR_ENABLE, currentWeight, *activeScaleSensorWeightSetPoint);
}

bool prevValue = false;

void displaymessage_helper(State activeState, char* displaymessagetext, char* displaymessagetext2) {
  DEBUG_print("displaymessage_helper active state: %d\n", activeState);

  if (softwareUpdateCheck()) {
     showSoftwareUpdate();
  } else 
  if (screenSaverCheck()) {
    showScreenSaver();
  } else if (menuCheck()) {
    showMenu(&displaymessagetext, &displaymessagetext2);
  } else {
    image_flip = !image_flip;

    bool showLastBrewStatistics = ( (brewTimer > 0) && (currentWeight != 0) && 
     (millis() <= brewStatisticsTimer + brewStatisticsAdditionalDisplayTime) ) ? true : false;

#if (ICON_COLLECTION == 3)
      // text only mode, nothing to do
#else
      // display icons
      switch (activeState) {
        case State::ColdStart:
        case State::StabilizeTemperature:
          showImage(StatusImage::Coldstart, image_flip);
          break;
        case State::BrewDetected: // brew
          showImage(StatusImage::Brewing, image_flip);
          showLastBrewStatistics = true; // always true within this state, makes "if" outside of case much easier to read
          break;
        case State::InnerZoneDetected:
          if (brewReady) {
            showImage(StatusImage::BrewReady, image_flip);
          } else { // inner zone
            showImage(StatusImage::BrewAcceptable, image_flip);
          }
          break;
        case State::OuterZoneDetected:
          if (Input >= steamReadyTemp) { // fallback: if hardware steaming button is used still show steaming icon
            showImage(StatusImage::Steam, image_flip);
          } else {
            showImage(StatusImage::OuterZone, image_flip);
          }
          break;
        case State::SteamMode: // steaming state (detected via controlAction STEAMING)
          if (Input >= steamReadyTemp) {
            showImage(StatusImage::Steam, image_flip);
          } else {
            // TODO create new icons for steam phase
            showImage(StatusImage::OuterZone, image_flip);
          }
          break;
        case State::SleepMode: // sleeping state
          display.clearBuffer();
          break;
        case State::CleanMode: // cleaning state
          showImage(StatusImage::Clean, image_flip);
          break;
      } // switch (activeState)
#endif

      // TODO: the next code block is very specific for the oled, make it more generic
      // the oled uses the same area for temperature and brewinfo and can only show one of them at the same time
      // the tft (240x240) is big enough to use different areas for both
#if (DISPLAY_HARDWARE != 4) // this shouldn't be here, for this we have the displaymanager
      bool clearTempView = prevValue != showLastBrewStatistics;
      if (clearTempView) {
        display.clearView(Area::Temperature);
      }
#endif
      if (showLastBrewStatistics) {
        showBrewingInfo();
      } else {
        showTemperatures(Input, *activeSetPoint, steaming);
      }

      prevValue = showLastBrewStatistics;
  }

  // power-off timer
#if (ENABLE_POWER_OFF_COUNTDOWN > 0)
  showPowerOffCountdown(displaymessagetext, displaymessagetext2);
#endif

  showStatusMessage(displaymessagetext, displaymessagetext2);

  // add status icons
  if (millis() >= 10000) {
    showStatusIcons();
    showProfileIcon();
  }
  display.sendBuffer();
}


void showProfileIcon() {

#ifndef DISPLAY_TEST
#if (ENABLE_PROFILE_STATUS == 0 || screenSaverOn)
  return;
#endif
if (ENABLE_PROFILE_STATUS == 2 && profile == 1) {
  return;
}
#endif

  Viewport profileIconView = display.getView(Area::ProfileIcon);
  uint16_t icon_x = profileIconView.getUpperRight().X - status_icon_width; // from right because of big icon setting, we calculate the x from right
  uint16_t icon_y = profileIconView.getLowerLeft().Y - status_icon_height; // lower because of big icon setting, we calculate the y bottom up

#ifdef DISPLAY_TEST
  if (profileIconIndex == 0) {
    display.clearRect(icon_x, icon_y, status_icon_width, status_icon_height);
    displayHelper.setCurrentProfileIcon(ProfileIcon::None);
    return;
  }
  profile = profileIconIndex;
#endif

  ProfileIcon currentIcon = static_cast<ProfileIcon>(profile);
  if (currentIcon != displayHelper.getCurrentProfileIcon()) {
    display.clearRect(icon_x, icon_y, status_icon_width, status_icon_height);
    display.drawImage(icon_x, icon_y, images.getProfileIcon(currentIcon));
    displayHelper.setCurrentProfileIcon(currentIcon);
  }
}

bool showAllStatusIcons() {
  return ENABLE_STATUS_ICONS == 2 && DISPLAY_HARDWARE == 4;
}

byte icon_counter_cache = 0;
void showStatusIcons() {
  byte icon_counter = 0;

  Viewport statusView = display.getView(Area::StatusIcons);
  uint16_t x = statusView.getUpperLeft().X;
  uint16_t y = statusView.getLowerLeft().Y - status_icon_height; // lower because of big icon setting, we calculate the y bottom up
  
  StatusIcon wifi = StatusIcon::None;
  StatusIcon blynk = StatusIcon::None;
  StatusIcon mqtt = StatusIcon::None;

#ifdef DISPLAY_TEST
  if (wifiIcon == "ok") wifi = StatusIcon::Wifi_Ok;
  if (wifiIcon == "nok") wifi = StatusIcon::Wifi_Not_Ok;
  if (wifiIcon == "off") wifi = StatusIcon::None;
  
  if (blynkIcon == "ok") blynk = StatusIcon::Blynk_Ok;
  if (blynkIcon == "nok") blynk = StatusIcon::Blynk_Not_Ok;
  if (blynkIcon == "off") blynk = StatusIcon::None;

  if (mqttIcon == "ok") mqtt = StatusIcon::Mqtt_Ok;
  if (mqttIcon == "nok") mqtt = StatusIcon::Mqtt_Not_Ok;
  if (mqttIcon == "off") mqtt = StatusIcon::None;
#elif (ENABLE_STATUS_ICONS == 0) 
  return;
#else 
  // TODO: use different icons depending on rssi, eg:
  // images.getStatusIcon(static_cast<StatusIcon>(rssi)) first segment rssi: e.g. 0-30, 31-60, 61-90, 91-120 (no bars)
  if ((!forceOffline && !isWifiWorking()) || (forceOffline && !FORCE_OFFLINE)) {
    wifi = StatusIcon::Wifi_Not_Ok;
  } else if (isWifiWorking() && showAllStatusIcons()) {
    wifi = StatusIcon::Wifi_Ok;
  }

  if (BLYNK_ENABLE && !isBlynkWorking() && !FORCE_OFFLINE) {
    blynk = StatusIcon::Blynk_Not_Ok;
  } else if (isBlynkWorking() && showAllStatusIcons()) {
    blynk = StatusIcon::Blynk_Ok;
  }

  if (MQTT_ENABLE && !isMqttWorking() && !FORCE_OFFLINE) {
    mqtt = StatusIcon::Mqtt_Not_Ok;
  } else if (isMqttWorking() && showAllStatusIcons()) {
    mqtt = StatusIcon::Mqtt_Ok;
  }
 #endif

  if (wifi != StatusIcon::None) {
    if (displayHelper.getStatusIconAtIndex(icon_counter) != wifi) {
      displayHelper.setStatusIconAtIndex(icon_counter, wifi);
      display.drawImage(x + (icon_counter * (status_icon_width - 1)), y, images.getStatusIcon(wifi));
    }
    icon_counter++;
  }

  if (blynk != StatusIcon::None) {
    if (displayHelper.getStatusIconAtIndex(icon_counter) != blynk) {
      displayHelper.setStatusIconAtIndex(icon_counter, blynk);
      display.drawImage(x + (icon_counter * (status_icon_width - 1)), y, images.getStatusIcon(blynk));
    }
    icon_counter++;
  }

  if (mqtt != StatusIcon::None) {
    if (displayHelper.getStatusIconAtIndex(icon_counter) != mqtt) {
      displayHelper.setStatusIconAtIndex(icon_counter, mqtt);
      display.drawImage(x + (icon_counter * (status_icon_width - 1)), y, images.getStatusIcon(mqtt));
    }
    icon_counter++;
  }

  int maxStatusIcons = 3;
  while (icon_counter < maxStatusIcons && icon_counter != icon_counter_cache) {
    displayHelper.setStatusIconAtIndex(icon_counter, StatusIcon::None);
    display.clearRect(x + (icon_counter * (status_icon_width - 1)), y, status_icon_width, status_icon_height);
    icon_counter++;
  }

  icon_counter_cache = icon_counter;
}

void showSoftwareUpdate() {
    display.clearBuffer();
    display.drawImageCentered(Area::SoftwareUpdate, update_icon_width, update_icon_height, update_bits);
    display.printCentered(Area::StatusMessage, (char*)"Updating Software");
}

void showScreenSaver() {
  static unsigned int screen_saver_x_pos = 41;
  static bool screen_saver_direction_right = true;
  const int unsigned screen_saver_step = 4;
  unsigned int logo_width_tmp = icon_width; // TODO: the hack with the width doesn't work anymore
  if (enableScreenSaver == 3 && strcmp(MACHINE_TYPE, "gaggia") == 0) {
    logo_width_tmp = 125; // hack which will result in logo only moving left
    screen_saver_x_pos = 5;
  } else if (enableScreenSaver == 3 && strcmp(MACHINE_TYPE, "ecm") == 0) {
    logo_width_tmp = 125; // hack which will result in logo only moving left
    screen_saver_x_pos = 11;
  }
  if (screen_saver_direction_right) {
    if (screen_saver_x_pos + screen_saver_step <= display.getWidth() - logo_width_tmp) {
      screen_saver_x_pos += screen_saver_step;
    } else {
      screen_saver_x_pos -= screen_saver_step;
      screen_saver_direction_right = false;
    }
  } else {
    if (screen_saver_x_pos >= screen_saver_step) {
      screen_saver_x_pos -= screen_saver_step;
    } else {
      screen_saver_x_pos += screen_saver_step;
      screen_saver_direction_right = true;
    }
  }
  if (enableScreenSaver == 1 || sleeping) {
    if (!screenSaverOn) { display.setPowerSave(1); }
  } else if (enableScreenSaver == 2) {
    display.clearBuffer();
    display.drawImage(screen_saver_x_pos, 0, icon_width, icon_height, images.getImage(StatusImage::BrewReady));
  } else if (enableScreenSaver == 3) {
    display.clearBuffer();
    display.drawImage(screen_saver_x_pos, 0, images.getLogo(StatusImage::MachineLogo));
  }
  screenSaverOn = true;
}

void showMenu(char** displaymessagetext, char** displaymessagetext2) {
  image_flip = !image_flip;
  unsigned int align_right;
  const unsigned int align_right_2digits = display.getWidth() - 56;
  const unsigned int align_right_3digits = display.getWidth() - 56 - 12;
  const unsigned int align_right_1digits_decimal = display.getWidth() - 56 + 12;
  menuMap* menuConfigPosition = getMenuConfigPosition(menuConfig, menuPosition);
  if (!menuConfigPosition) return;
  showImage(StatusImage::Menu, image_flip);
  display.setFont(FontType::Big);
  if (!strcmp(menuConfigPosition->value->type, "bool")) {
    bool menuValue;
    if (menuConfigPosition->value->is_double_ptr) {
      menuValue = **(int**)menuConfigPosition->value->ptr;
    } else {
      menuValue = *(int*)menuConfigPosition->value->ptr;
    }
    display.setCursor(align_right_2digits, 3);
    if ( menuValue == 0) {
      display.print("Off");
    } else {
      display.print("On");
    }
  }
  else if (!strcmp(menuConfigPosition->value->type, "int")) {
    int menuValue;
    if (menuConfigPosition->value->is_double_ptr) {
      menuValue = **(int**)menuConfigPosition->value->ptr;
    } else {
      menuValue = *(int*)menuConfigPosition->value->ptr;
    }
    if (menuValue >= 100) {
          align_right = align_right_3digits;
        } else {
          if (menuValue >= 10) {
            align_right = align_right_2digits;
          } else align_right = align_right_1digits_decimal;
    }
    display.setCursor(align_right, 3);
    display.print(menuValue, 1);
  } else {
    float menuValue;
    if (menuConfigPosition->value->is_double_ptr) {
      menuValue = **(float**)menuConfigPosition->value->ptr;
    } else {
      menuValue = *(float*)menuConfigPosition->value->ptr;
    }
    if (menuValue - 100 > -FLT_EPSILON) {
          align_right = align_right_3digits;
        } else {
          if (menuValue >= 10) {
            align_right = align_right_2digits;
          } else align_right = align_right_1digits_decimal;
    }
    display.setCursor(align_right, 3);
    display.print(menuValue, 1);
  }
  char* unit = menuConfigPosition->unit;
  if (!unit) {
  } else if (strcmp(unit, "C") == 0) {
    display.setFont(FontType::Small);
    display.print((char)176);
    display.println(unit);
  } else {
    display.setFont(FontType::Small);
    display.println(unit);
  }
  *displaymessagetext = (char*)"";
  *displaymessagetext2 = (char*) convertDefineToReadableVariable(menuConfigPosition->item);
}

void showPowerOffCountdown(char* displaymessagetext, char* displaymessagetext2) {
  powerOffTimer = ENABLE_POWER_OFF_COUNTDOWN - ((millis() - lastBrewEnd) / 1000);
  if (powerOffTimer <= powerOffCountDownStart && !brewing && !strlen(displaymessagetext) && !strlen(displaymessagetext2)) {
    display.printCountdown(powerOffTimer);
  }
}

/************************************
* new implementations
*************************************/
void InitDisplay() {
  display.init();
}

void showBootLogo() {
  display.drawImageCentered(Area::BootLogo, logo_width, logo_height, logo_bits);
}

void hideBootLogo() {
  display.clearView(Area::BootLogo);
}

void clearDisplay() {
  display.clearBuffer();
}

void showBootMessage(char* displaymessagetext) {
  showBootMessage(displaymessagetext, (char*)"");
}

void showBootMessage(char* displaymessagetext, char* displaymessagetext2) {
#if ENABLE_BOOT_MESSAGES == 1  
  display.setFont(FontType::Normal);
  hideBootMessage();
  display.printCentered(Area::BootMessage, displaymessagetext, displaymessagetext2);
#endif  
}

void hideBootMessage() {
  display.clearView(Area::BootMessage);  
}

void showStatusMessage(char* displaymessagetext) {
  showStatusMessage(displaymessagetext, (char*)"");
}

void showStatusMessage(char* displaymessagetext, char* displaymessagetext2) {
  showStatusMessage(displaymessagetext, displaymessagetext2, true);
}


void showStatusMessage(char* displaymessagetext, char* displaymessagetext2, bool useBuffering) {
  if (isEmpty(displaymessagetext) && isEmpty(displaymessagetext2)) {
    return;
  }

  if (useBuffering) {
    int same1 = strcmp(displaymessagetext, displayMessageLine1Cache);
    int same2 = strcmp(displaymessagetext2, displayMessageLine2Cache);
    if (same1 == 0 && same2 == 0) {  
      return; // same text, no need to update display
    }
    if (same1 != 0) { strcpy(displayMessageLine1Cache, displaymessagetext); }
    if (same2 != 0) { strcpy(displayMessageLine2Cache, displaymessagetext2); }
  }

  display.setFont(FontType::Normal);
  display.clearView(Area::StatusMessage);
  display.printCentered(Area::StatusMessage, displaymessagetext, displaymessagetext2);
}

void hideStatusMessage() {
  display.clearView(Area::StatusMessage);
}
