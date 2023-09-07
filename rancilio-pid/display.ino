/***********************************
 *  DISPLAY
 ***********************************/
#include <float.h>
#include "display.h"
#include "rancilio-debug.h"
#include "rancilio-network.h"

#include "display/ImageDictionary.h"

#include "display/DisplayManager.h"
extern DisplayManager display;  // declare the extern DisplayManager object to use the same instance everywhere

unsigned long previousMillisDisplay = 0; // initialisation at the end of init()
const long intervalDisplay = 1000; // update for display
bool image_flip = true;
unsigned int enableScreenSaver = ENABLE_SCREEN_SAVER;
bool screenSaverOn = false;
const unsigned int powerOffCountDownStart = 300;


ImageDictionary images;

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
void displaymessage_esp32_task(void* activeStateParam) {
  //display.init();
  delay(100);
  for (;;) {
    // unsigned long cur_micros_display = micros();
    displaymessage_helper(activeStateBuffer, displaymessagetextBuffer, displaymessagetext2Buffer);
    // DEBUG_print("inside displaymessage_esp32_task() done =%lu\n", micros()-cur_micros_display);
    vTaskDelay(intervalDisplay / portTICK_PERIOD_MS);
  }
  vTaskDelete(NULL);
}
#endif

void displaymessage(State activeState, char* displaymessagetext, char* displaymessagetext2) {
  if (Display > 0) {
    static int only_once = 0;
#ifdef ESP32
    // DEBUG_print("activeState=%d | %s | %s\n", activeState, displaymessagetext, displaymessagetext2);
    if ((millis() >= previousMillisDisplay + intervalDisplay) || only_once == 0) {
      previousMillisDisplay = millis();
      activeStateBuffer = activeState;
      setDisplayTextState(activeStateBuffer, displaymessagetext, displaymessagetext2);
    }
    if (only_once == 0) {
      only_once = 1;
      xTaskCreatePinnedToCore(displaymessage_esp32_task, /* Task function. */
          "displaymessage", /* name of task. */
          2000, /* Stack size of task */
          (void*)&activeState, /* parameter of the task */
          6, /* priority of the task */
          NULL, /* Task handle to keep track of created task */
          0); /* pin task to core 1 */
    }
#else
    if (only_once == 0) {
      only_once = 1;
      //display.init();
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
  if (image_flip) {
    display.drawImageCentered(Area::ActionImage, icon_width, icon_height, images.getImage(image));
  } else {
    display.drawImageCentered(Area::ActionImage, icon_width, icon_height, images.getImageRotated(image));
  }
}


void showTemperatures(float t1, float t2, bool steaming) {
  display.printTemperatures(t1, t2, steaming);
}

void showBrewingInfo() {
      totalBrewTime = ( (OnlyPID || BREWTIME_TIMER == 0 )? *activeBrewTime : *activePreinfusion + *activePreinfusionPause + *activeBrewTime) * 1000;
      unsigned int align_right_left_value = display.getWidth() - 56 - 5;
      unsigned int align_right_right_value = display.getWidth() - 56 + 28;
      display.setFont(FontType::Big);
      display.setCursor(align_right_left_value, 3);
      if (brewTimer < 10000) display.print("0");
      // TODO: Use print(u8x8_u8toa(value, digits)) or print(u8x8_u16toa(value, digits)) to print numbers with constant width (numbers are prefixed with 0 if required).
      display.print(brewTimer / 1000);

      display.setFont(FontType::OpenIconicArrow);
      display.drawGlyph(align_right_right_value - 8, 3 + 6, 0x04e);
      display.setFont(FontType::Big);
      display.setCursor(align_right_right_value, 3);
      display.print(totalBrewTime / 1000);

      display.setFont(FontType::Small);
      display.println("s");

      if (SCALE_SENSOR_ENABLE) {
        display.setFont(FontType::Big);
        display.setCursor(align_right_left_value, 20);
        int weight = (int) currentWeight;
        //if (weight <0) weight = 0;
        if (weight < 10) display.print("0");
        display.print(weight<0?0:weight, 0);

        display.setFont(FontType::OpenIconicArrow);
        display.drawGlyph(align_right_right_value - 8, 20 + 6, 0x04e);
        display.setFont(FontType::Big);
        display.setCursor(align_right_right_value, 20);
        display.print(*activeScaleSensorWeightSetPoint, 0);

        display.setFont(FontType::Small);
        display.println("g");
      }
      //display.setFont(FontType::OpenIconicOther);
      display.setFont(FontType::OpenIconicThing);
      if (*activeBrewTimeEndDetection == 0) {
        display.drawGlyph(align_right_left_value - 11, 3 + 6, 0x04f);
      } else {
        display.drawGlyph(align_right_left_value - 11, 20 + 6, 0x04f);
      }
}

void displaymessage_helper(State activeState, char* displaymessagetext, char* displaymessagetext2) {
  display.clearBuffer();
  display.setBitmapMode(1);

  if (softwareUpdateCheck()) {
    showSoftwareUpdate();
  } else if (screenSaverCheck()) {
    showScreenSaver();
  } else if (menuCheck()) {
    showMenu(&displaymessagetext, &displaymessagetext2);
  } else {
    image_flip = !image_flip;

    bool showLastBrewStatistics = ( (brewTimer > 0) && (currentWeight != 0) && 
     (millis() <= brewStatisticsTimer + brewStatisticsAdditionalDisplayTime) ) ? true : false;

#if (ICON_COLLECTION == 3)
      // text only mode
      // I deleted the code in here, why drawImage in text only mode?
#else
      // display icons
      switch (activeState) {
        case State::ColdStart:
        case State::StabilizeTemperature:
          showImage(StatusImage::Coldstart, image_flip);
          break;
        case State::BrewDetected: // brew
          showImage(StatusImage::Brewing, image_flip);
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
          break;
        case State::CleanMode: // cleaning state
          showImage(StatusImage::Clean, image_flip);
          break;
      } // switch (activeState)
#endif
   // }

    // display current and target temperature
    if (activeState != State::Undefined && activeState != State::BrewDetected && !showLastBrewStatistics) {
      showTemperatures(Input, *activeSetPoint, steaming);
    } else if (activeState == State::BrewDetected || showLastBrewStatistics) {  //brew
      showBrewingInfo();
    }
  }

  // power-off timer
#if (ENABLE_POWER_OFF_COUNTDOWN > 0)
  showPowerOffCountdown(displaymessagetext, displaymessagetext2);
#endif

  showStatusMessage(displaymessagetext, displaymessagetext2);

  // add status icons
  if (millis() >= 10000) {
    showStatusIcons();
  }
  display.sendBuffer();
}

void showStatusIcons() { 
    byte icon_y = display.getHeight() - (status_icon_height - 1);
    byte icon_counter = 0;
    #if (ENABLE_PROFILE_STATUS > 0 && !screenSaverOn)
      if (profile == 1 && ENABLE_PROFILE_STATUS == 1) {
        display.drawImage(icon_counter * (status_icon_width - 1), icon_y, status_icon_width, status_icon_height, profile_1_bits);
        icon_counter++;
      } else if (profile == 2) { 
        display.drawImage(icon_counter * (status_icon_width - 1), icon_y, status_icon_width, status_icon_height, profile_2_bits);
        icon_counter++;
      } else if (profile == 3) {
        display.drawImage(icon_counter * (status_icon_width - 1), icon_y, status_icon_width, status_icon_height, profile_3_bits);
        icon_counter++;
      }
    #endif
    #if (ENABLE_FAILURE_STATUS_ICONS == 1)
      if (image_flip) {   
        if ((!forceOffline && !isWifiWorking()) || (forceOffline && !FORCE_OFFLINE)) {
          display.drawImage(icon_counter * (status_icon_width - 1), icon_y, status_icon_width, status_icon_height, wifi_not_ok_bits);
          icon_counter++;
        }
        if (BLYNK_ENABLE && !isBlynkWorking() && !FORCE_OFFLINE) {
          display.drawImage(icon_counter * (status_icon_width - 1), icon_y, status_icon_width, status_icon_height, blynk_not_ok_bits);
          icon_counter++;
        }
        if (MQTT_ENABLE && !isMqttWorking() && !FORCE_OFFLINE) {
          display.drawImage(icon_counter * (status_icon_width - 1), icon_y, status_icon_width, status_icon_height, mqtt_not_ok_bits);
          icon_counter++;
        }
      }
    #endif
}


void showSoftwareUpdate() {
    int posX = (display.getWidth() - update_icon_width) / 2;
    display.drawImage(posX, 0, update_icon_width, update_icon_height, update_bits);
}

void showScreenSaver() {
  static unsigned int screen_saver_x_pos = 41;
  static bool screen_saver_direction_right = true;
  const int unsigned screen_saver_step = 4;
  unsigned int logo_width_tmp = icon_width;
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
    display.drawImage(screen_saver_x_pos, 0, icon_width, icon_height, brew_ready_bits);
  } else if (enableScreenSaver == 3) {
    display.drawImage(screen_saver_x_pos, 0, logo_width_tmp, logo_height, logo_bits);
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
  *displaymessagetext2 = (char*) convertDefineToReadAbleVariable(menuConfigPosition->item);
}

void showPowerOffCountdown(char* displaymessagetext, char* displaymessagetext2) {
  const unsigned int align_right_countdown_min = display.getWidth() - 52;
  const unsigned int align_right_countdown_sec = display.getWidth() - 52 + 20;
  static char line[30];
  powerOffTimer = ENABLE_POWER_OFF_COUNTDOWN - ((millis() - lastBrewEnd) / 1000);
  if (powerOffTimer <= powerOffCountDownStart && !brewing && !strlen(displaymessagetext) && !strlen(displaymessagetext2)) {
    display.setFont(FontType::OpenIconicEmbedded);
    display.drawGlyph(align_right_countdown_min - 15, 37 + 6, 0x004e);
    display.setFont(FontType::Big);
    display.setCursor(align_right_countdown_min, 37);
    snprintf(line, sizeof(line), "%d", int(powerOffTimer / 60));
    display.print(line);
    display.setFont(FontType::Small);
    display.println("m");
    display.setFont(FontType::Big);
    display.setCursor(align_right_countdown_sec, 37);
    snprintf(line, sizeof(line), "%02d", int(powerOffTimer % 60));
    display.print(line);
    display.setCursor(align_right_countdown_sec + 23, 37);
    display.setFont(FontType::Small);
    display.println(" s");
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
  display.setFont(FontType::Normal);
  //hideStatusMessage();
  // status messages are shown in the lower half of the display
  // upper half is for icons und stuff
  int posY = 40; //display.getHeight() / 2;
  display.printCentered(displaymessagetext, displaymessagetext2, posY);
}

void hideStatusMessage() {
  // status messages are shown in the lower half of the display
  // upper half is for icons und stuff
  int posY = 40; // display.getHeight() / 2;
  display.clearRect(0, posY, display.getWidth(), display.getHeight() - posY);
}

