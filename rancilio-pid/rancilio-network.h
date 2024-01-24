#ifndef _rancilio_network_h
#define _rancilio_network_h

#include "Arduino.h"

bool InitNetworking();
void checkWifi(bool);
void HandleOTA();
void InitOTA();
bool isWifiWorking();

extern bool forceOffline;

extern int8_t wifi_rssi; // -120 to 0 (0 is best, -90 to -120 unusable)

#endif