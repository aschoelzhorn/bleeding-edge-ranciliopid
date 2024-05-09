#pragma once

#include <Arduino.h>

struct WifiData {
    boolean isConnected;
    int signalStrength;
    unsigned int reconnects;
};