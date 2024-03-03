#ifndef _rancilio_network_h
#define _rancilio_network_h

#include "Arduino.h"

bool InitNetworking();
void checkWifi(bool);
void HandleOTA();
void InitOTA();
bool isWifiWorking();

extern bool forceOffline;

extern int8_t wifi_rssi; // -120 to 0 (0 is best, -90 to -120 unusable), 
/*
void getSignalStrength() {
    if (offlineMode == 1) return;

    long rssi;

    if (WiFi.status() == WL_CONNECTED) {
        rssi = WiFi.RSSI();
    }
    else {
        rssi = -100;
    }

    if (rssi >= -50) {
        signalBars = 4;
    }
    else if (rssi < -50 && rssi >= -65) {
        signalBars = 3;
    }
    else if (rssi < -65 && rssi >= -75) {
        signalBars = 2;
    }
    else if (rssi < -75 && rssi >= -80) {
        signalBars = 1;
    }
    else {
        signalBars = 0;
    }
}

*/

#endif