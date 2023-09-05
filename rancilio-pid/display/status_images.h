#pragma once

#ifndef status_images_h
#define status_images_h

enum class StatusImage {
    Coldstart = 0,
    Brewing = 1,
    BrewReady = 2,
    BrewAcceptable = 3,
    Steam = 4,
    OuterZone = 5,
    Clean = 6,
    Menu = 7,
    SoftwareUpdate = 8,
    MachineLogo = 9,
    GenericLogo = 10,
    Test = 11
};

enum class StatusIcon {
    Profile_1 = 0,
    Profile_2 = 1,
    Profile_3 = 2,
    Wifi_Not_Ok = 3,
    Blynk_Not_Ok = 4,
    Mqtt_Not_Ok = 5
};

#endif