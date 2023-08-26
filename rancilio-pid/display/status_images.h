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
    SoftwareUpdate = 8
};

enum class StatusIcon {
    Profile_1 = 0,
    Profile_2 = 1,
    Profile_3 = 2,
    Wifi_Not_Ok = 3,
    Blynk_Not_Ok = 4,
    Mqtt_Not_Ok = 5
};

// std::map<StatusImage, const unsigned char*> imageDictionary = {
//     {StatusImage::Coldstart, coldstart_bits},
//     {StatusImage::Brewing, brewing_bits},
//     {StatusImage::BrewReady, brew_ready_bits},
//     {StatusImage::BrewAcceptable, brew_acceptable_bits},
//     {StatusImage::Steam, steam_bits},
//     {StatusImage::OuterZone, outer_zone_bits},
//     {StatusImage::Clean, clean_bits},
//     {StatusImage::Menu, menu_bits}
// };

// std::map<StatusImage, const unsigned char*> imageRotatedDictionary = {
//     {StatusImage::Coldstart, coldstart_rotate_bits},
//     {StatusImage::Brewing, brewing_rotate_bits},
//     {StatusImage::BrewReady, brew_ready_rotate_bits},
//     {StatusImage::BrewAcceptable, brew_acceptable_rotate_bits},
//     {StatusImage::Steam, steam_rotate_bits},
//     {StatusImage::OuterZone, outer_zone_rotate_bits},
//     {StatusImage::Clean, clean_rotate_bits},
//     {StatusImage::Menu, menu_rotate_bits}
// };


#endif