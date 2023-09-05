#pragma once

#ifndef IMAGE_DICTIONARY_h
#define IMAGE_DICTIONARY_h

#include <map>
#include "status_images.h"  // Include the enum

#include "../userConfig.h"

#include <pgmspace.h>

#if DISPLAY_HARDWARE == 4

// #define g_logo_width 216
// #define g_logo_height 131

using LogoType = uint16_t;
// using LogoData = std::array<LogoType, g_logo_width * g_logo_height>;

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

#else

using LogoType = const char;
#ifdef MACHINE_TYPE_GAGGIA
#include "icons/icon_gaggia.h"
#elif defined(MACHINE_TYPE_ECM)
#include "icons/icon_ecm.h"
#elif defined(MACHINE_TYPE_RANCILIO)
#include "icons/icon_rancilio.h"
#else
#include "icons/icon_generic.h"
#endif

#include "icons/icon_shared.h"
#endif

#if (ENABLE_BIG_STATUS_ICONS)
#include "icons/icon_big.h"
#else
#include "icons/icon.h"
#endif
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

     // void init();

     const LogoType* getLogo(StatusImage);
     const unsigned char* getImage(StatusImage);
     const unsigned char* getImageRotated(StatusImage);
     const unsigned char* getStatusIcon(StatusIcon);
     
     //std::map<StatusImage, LogoType*> logoDictionary;
private:
     std::map<StatusImage, const LogoType*> logoDictionary;
     std::map<StatusImage, const unsigned char*> imageDictionary;
     std::map<StatusImage, const unsigned char*> imageRotatedDictionary;
     std::map<StatusIcon, const unsigned char*> statusIconDictionary;
};

#endif // IMAGE_DICTIONARY_h