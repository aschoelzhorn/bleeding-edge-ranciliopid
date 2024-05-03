#pragma once

#include <Arduino.h>

struct StateData {
    int offlineMode;
    boolean waterFull;
    unsigned int isrCounter;

    int flushCycles;
    int maxflushCycles;
    int backflushState;
};