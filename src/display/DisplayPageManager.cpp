#include "DisplayPageManager.h"

#include "templates/DisplayPageStandard.h"
#include "templates/DisplayPageMinimal.h" 
#include "templates/DisplayPageTemperatureOnly.h" 
// #include "templates/DisplayPageScale.h" 
#include "templates/DisplayPageColor.h" 

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