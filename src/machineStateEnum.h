/**
 * @file machineStateEnum.h
 *
 * @brief state enum for machine
 *
 */

#pragma once

enum MachineState {
    kInit = 0,
    kPidNormal = 20,
    kBrew = 30,
    kShotTimerAfterBrew = 31,
    kBrewDetectionTrailing = 35,
    kSteam = 40,
    kCoolDown = 45,
    kBackflush = 50,
    kWaterEmpty = 70,
    kEmergencyStop = 80,
    kPidDisabled = 90,
    kStandby = 95,
    kSensorError = 100,
    kEepromError = 110,
};
