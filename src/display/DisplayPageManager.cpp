#include "DisplayPageManager.h"

// #include "../userConfig.h"
// #if (DISPLAY_HARDWARE == 4)
// #define TFT_eSPI_DISPLAY
// #include "displayPageTypeEnumTFT.h"
// #elif (DISPLAY_HARDWARE == 1) || (DISPLAY_HARDWARE == 2) || (DISPLAY_HARDWARE == 3)
// #define U8G2_DISPLAY
// #include "displayPageTypeOLEDEnum.h"
// #else
// #define NO_DISPLAY
// #endif

#include "DisplayPageStandard.h"
#include "DisplayPageMinimal.h" 
#include "DisplayPageTemperatureOnly.h" 
// #include "DisplayPageScale.h" 
#include "DisplayPageColor.h" 

DisplayPageManager::DisplayPageManager(DisplayManager *instanceOfDisplayManager) {
    displayManager = instanceOfDisplayManager;
}

IDisplayPage *DisplayPageManager::getPage(DisplayPageType pageType) {
    // return correct instance of DisplayPage
    switch (pageType) {
        case DisplayPageType::Standard: {
            page = new DisplayPageStandard(displayManager);
            break;
        }
        case DisplayPageType::Minimal: {
            page = new DisplayPageMinimal(displayManager);
            break;
        }
        case DisplayPageType::TemperatureOnly: {
            page = new DisplayPageTemperatureOnly(displayManager);
            break;
        }
        case DisplayPageType::Scale: {
            //page = new DisplayPageScale(displayManager);
            break;
        }
        case DisplayPageType::Color: {
            page = new DisplayPageColor(displayManager);
            break;
        }
        default: {
            // error? or just use standard?
            // page = new DisplayPageStandard(displayManager);
            break;    
        }
    }

    return page;
}