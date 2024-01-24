#pragma once

#ifndef IMAGE_DICTIONARY_h
#define IMAGE_DICTIONARY_h

#include <map>
#include "status_images.h"  // Include the enum
#include "../userConfig.h"
#include <pgmspace.h>

#if DISPLAY_HARDWARE == 4

using LogoType = uint16_t;

#ifdef MACHINE_TYPE_GAGGIA
#include "icons/icon_gaggia_color.h"
#elif defined(MACHINE_TYPE_ECM)
#include "icons/icon_ecm_color.h"
#elif defined(MACHINE_TYPE_RANCILIO)
#include "icons/icon_rancilio_color.h"
#else
#include "icons/icon_generic_color_.h"
#endif
#include "icons/icon_shared_color.h"
#include "icons/icon_color.h"

#else // DISPLAY_HARDWARE

using LogoType = const unsigned char;
#ifdef MACHINE_TYPE_GAGGIA
#include "icons/icon_gaggia.h"
#elif defined(MACHINE_TYPE_ECM)
#include "icons/icon_ecm.h"
#elif defined(MACHINE_TYPE_RANCILIO)
#include "icons/icon_rancilio.h"
#else
#include "icons/icon_generic.h"
#endif

#if (ENABLE_BIG_STATUS_ICONS)
#include "icons/icon_big.h"
#else
#include "icons/icon.h"
#endif

#include "icons/icon_shared.h"
#endif // DISPLAY_HARDWARE

#if (ICON_COLLECTION == 2)
#include "icons/icon_winter.h"
#elif (ICON_COLLECTION == 1)
#include "icons/icon_smiley.h"
#else
#include "icons/icon_simple.h" // also used as placeholder for ICON_COLLECTION==3
#endif

class ImageDictionary {
public:
     ImageDictionary();

     const LogoType* getLogo(StatusImage);
     const unsigned char* getImage(StatusImage);
     const unsigned char* getImageRotated(StatusImage);
     const LogoType* getStatusIcon(StatusIcon);
     const LogoType* getProfileIcon(ProfileIcon);

// add some pointers to make it compile without "ok status icons"
#if DISPLAY_HARDWARE < 4 
     const LogoType* wifi_ok_bits = wifi_not_ok_bits;
     const LogoType* blynk_ok_bits = blynk_not_ok_bits;
     const LogoType* mqtt_ok_bits = mqtt_not_ok_bits;
#endif

private:
     std::map<StatusImage, const LogoType*> logoDictionary;
     std::map<StatusImage, const unsigned char*> imageDictionary;
     std::map<StatusImage, const unsigned char*> imageRotatedDictionary;
     std::map<StatusIcon, const LogoType*> statusIconDictionary;
     std::map<ProfileIcon, const LogoType*> profileIconDictionary;
};


// TODO: check if we should use this struct to store in the ImageDictionary, so we can also read the size dynamically (e.g. smaller status icons for smaller displays)
/*
 typedef struct {
     const uint16_t *data;
     uint16_t width;
     uint16_t height;
     uint8_t dataSize;
     } tImage;
*/

#endif // IMAGE_DICTIONARY_h