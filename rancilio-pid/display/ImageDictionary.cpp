// ImageDictionary.cpp

#include "ImageDictionary.h"

ImageDictionary::ImageDictionary() {
    std::map<StatusImage, const unsigned char*> imageDictionary = {
    {StatusImage::Coldstart, coldstart_bits},
    {StatusImage::Brewing, brewing_bits},
    {StatusImage::BrewReady, brew_ready_bits},
    {StatusImage::BrewAcceptable, brew_acceptable_bits},
    {StatusImage::Steam, steam_bits},
    {StatusImage::OuterZone, outer_zone_bits},
    {StatusImage::Clean, clean_bits},
    {StatusImage::Menu, menu_bits}
};

std::map<StatusImage, const unsigned char*> imageRotatedDictionary = {
    {StatusImage::Coldstart, coldstart_rotate_bits},
    {StatusImage::Brewing, brewing_rotate_bits},
    {StatusImage::BrewReady, brew_ready_rotate_bits},
    {StatusImage::BrewAcceptable, brew_acceptable_rotate_bits},
    {StatusImage::Steam, steam_rotate_bits},
    {StatusImage::OuterZone, outer_zone_rotate_bits},
    {StatusImage::Clean, clean_rotate_bits},
    {StatusImage::Menu, menu_rotate_bits}
};

std::map<StatusIcon, const unsigned char*> statusIconDictionary = {
    {StatusIcon::Profile_1, profile_1_bits},
    {StatusIcon::Profile_2, profile_2_bits},
    {StatusIcon::Profile_3, profile_3_bits},
    {StatusIcon::Wifi_Not_Ok, wifi_not_ok_bits},
    {StatusIcon::Blynk_Not_Ok, blynk_not_ok_bits},
    {StatusIcon::Mqtt_Not_Ok, mqtt_not_ok_bits}
};

}

const unsigned char* ImageDictionary::getImage(StatusImage image) {
    return imageDictionary[image];
};
const unsigned char* ImageDictionary::getImageRotated(StatusImage image){
    return imageRotatedDictionary[image];
}
const unsigned char* ImageDictionary::getStatusIcon(StatusIcon icon) {
    return statusIconDictionary[icon];
}


// const unsigned char* ImageDictionary::getStatusImage(StatusImage image) {
//     return imageDictionary[image];
// }

// const unsigned char* ImageDictionary::getStatusImageRotated(StatusImage image) {
//     return imageRotatedDictionary[image];
// }


