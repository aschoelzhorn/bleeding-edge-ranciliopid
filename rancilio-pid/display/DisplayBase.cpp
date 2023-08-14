#include "DisplayBase.h"

DisplayBase::DisplayBase() {
    // Common initialization code if needed
}

bool DisplayBase::softwareUpdateCheck() {
  return activeState == State::SoftwareUpdate;
}

bool DisplayBase::menuCheck() {
  if (menuPosition != 0 && (millis() <= previousTimerMenuCheck + menuOffTimer) ) {
    return true;
  } else {
    menuPosition = 0;
    return false;
  }
}

char* DisplayBase::outputSimpleState() {
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

void DisplayBase::setDisplayTextState(State activeState, char* displaymessagetext, char* displaymessagetext2) {
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
