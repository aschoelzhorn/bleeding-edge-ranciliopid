#ifndef STATE_H
#define STATE_H

#pragma once

enum class State {
  Undefined = 0,
  ColdStart = 1,
  StabilizeTemperature = 2,
  InnerZoneDetected = 3,  // == default
  BrewDetected = 4,
  OuterZoneDetected = 5,
  SteamMode = 6,
  SleepMode = 7,
  CleanMode = 8,
  SoftwareUpdate = 9
};

#endif