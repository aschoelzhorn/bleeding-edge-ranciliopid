// ImageDictionary.cpp

#include "ImageDictionary.h"

#include <Arduino.h>

// using LogoData = std::array<LogoType, logo_width * logo_height>;

// std::map<StatusImage, LogoData> ImageDictionary::logoDictionary;

ImageDictionary::ImageDictionary() {
    // std::map<StatusImage, LogoType*> 
    logoDictionary = {
           {StatusImage::MachineLogo, logo_bits},
           {StatusImage::GenericLogo, generic_logo_bits}
    };

    imageDictionary = {
        {StatusImage::Coldstart, coldstart_bits},
        {StatusImage::Brewing, brewing_bits},
        {StatusImage::BrewReady, brew_ready_bits},
        {StatusImage::BrewAcceptable, brew_acceptable_bits},
        {StatusImage::Steam, steam_bits},
        {StatusImage::OuterZone, outer_zone_bits},
        {StatusImage::Clean, clean_bits},
        {StatusImage::Menu, menu_bits},
        {StatusImage::SoftwareUpdate, update_bits},
        {StatusImage::Test, test_bits}
    };

    imageRotatedDictionary = {
        {StatusImage::Coldstart, coldstart_rotate_bits},
        {StatusImage::Brewing, brewing_rotate_bits},
        {StatusImage::BrewReady, brew_ready_rotate_bits},
        {StatusImage::BrewAcceptable, brew_acceptable_rotate_bits},
        {StatusImage::Steam, steam_rotate_bits},
        {StatusImage::OuterZone, outer_zone_rotate_bits},
        {StatusImage::Clean, clean_rotate_bits},
        {StatusImage::Menu, menu_rotate_bits}
    };

    statusIconDictionary = {
        {StatusIcon::Profile_1, profile_1_bits},
        {StatusIcon::Profile_2, profile_2_bits},
        {StatusIcon::Profile_3, profile_3_bits},
        {StatusIcon::Wifi_Not_Ok, wifi_not_ok_bits},
        {StatusIcon::Blynk_Not_Ok, blynk_not_ok_bits},
        {StatusIcon::Mqtt_Not_Ok, mqtt_not_ok_bits}
    };   
}

// void ImageDictionary::init() {
//    Serial.println("ImageDictionary: setting up image maps in init");

    // imageDictionary = {
    //     {StatusImage::Coldstart, coldstart_bits},
    //     {StatusImage::Brewing, brewing_bits},
    //     {StatusImage::BrewReady, brew_ready_bits},
    //     {StatusImage::BrewAcceptable, brew_acceptable_bits},
    //     {StatusImage::Steam, steam_bits},
    //     {StatusImage::OuterZone, outer_zone_bits},
    //     {StatusImage::Clean, clean_bits},
    //     {StatusImage::Menu, menu_bits},
    //     {StatusImage::SoftwareUpdate, update_bits},
    //     {StatusImage::Test, test_bits}
    // };

    // imageRotatedDictionary = {
    //     {StatusImage::Coldstart, coldstart_rotate_bits},
    //     {StatusImage::Brewing, brewing_rotate_bits},
    //     {StatusImage::BrewReady, brew_ready_rotate_bits},
    //     {StatusImage::BrewAcceptable, brew_acceptable_rotate_bits},
    //     {StatusImage::Steam, steam_rotate_bits},
    //     {StatusImage::OuterZone, outer_zone_rotate_bits},
    //     {StatusImage::Clean, clean_rotate_bits},
    //     {StatusImage::Menu, menu_rotate_bits}
    // };

    // statusIconDictionary = {
    //     {StatusIcon::Profile_1, profile_1_bits},
    //     {StatusIcon::Profile_2, profile_2_bits},
    //     {StatusIcon::Profile_3, profile_3_bits},
    //     {StatusIcon::Wifi_Not_Ok, wifi_not_ok_bits},
    //     {StatusIcon::Blynk_Not_Ok, blynk_not_ok_bits},
    //     {StatusIcon::Mqtt_Not_Ok, mqtt_not_ok_bits}
    // };    
// }

const LogoType* ImageDictionary::getLogo(StatusImage image) {
    return logoDictionary[image];
}

const unsigned char* ImageDictionary::getImage(StatusImage image) {
    return imageDictionary[image];
}

const unsigned char* ImageDictionary::getImageRotated(StatusImage image){
    return imageRotatedDictionary[image];
}

const unsigned char* ImageDictionary::getStatusIcon(StatusIcon icon) {
    return statusIconDictionary[icon];
}
