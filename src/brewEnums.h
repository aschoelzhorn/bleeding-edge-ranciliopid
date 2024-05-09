/**
 * @file brewEnums.h
 *
 * @brief enums for Handler for brewing
 *
 */

#pragma once

enum BrewSwitchState {
    kBrewSwitchIdle = 10,
    kBrewSwitchBrew = 20,
    kBrewSwitchBrewAbort = 30,
    kBrewSwitchFlushOff = 31,
    kBrewSwitchReset = 40
};

enum BrewState {
    kBrewIdle = 10,
    kPreinfusion = 20,
    kWaitPreinfusion = 21,
    kPreinfusionPause = 30,
    kWaitPreinfusionPause = 31,
    kBrewRunning = 40,
    kWaitBrew = 41,
    kBrewFinished = 42,
    kWaitBrewOff = 43
};

enum BackflushState {
    kBackflushWaitBrewswitchOn = 10,
    kBackflushFillingStart = 20,
    kBackflushFilling = 21,
    kBackflushFlushingStart = 30,
    kBackflushFlushing = 31,
    kBackflushWaitBrewswitchOff = 43
};
