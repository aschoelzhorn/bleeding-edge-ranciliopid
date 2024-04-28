#include "DisplayPageManager.h"

#include "DisplayPageTemperatureOnly.h" 
#include "DisplayPageMinimal.h" 

DisplayPageManager::DisplayPageManager(DisplayManager *instanceOfDisplayManager) {
    displayManager = instanceOfDisplayManager;
}

DisplayPage *DisplayPageManager::getPage(DisplayPageType pageType) {
    // return correct instance of DisplayPage
    switch (pageType) {
        case DisplayPageType::TemperatureOnly: {
            page = new DisplayPageTemperatureOnly(displayManager);
            break;
        }
        case DisplayPageType::Minimal: {
            page = new DisplayPageMinimal(displayManager);
            break;
        }
        case DisplayPageType::Scale: {
            // DisplayPageScale *tmp = new DisplayPageScale(displayManager);
            // page = tmp;
            break;
        }
        case DisplayPageType::Standard: {
            // DisplayPageStandard *tmp = new DisplayPageStandard(displayManager);
            // page = tmp;
            break;
        }
        default: {
            // error? or just use standard?
            // DisplayPageStandard *tmp = new DisplayPageStandard(displayManager);
            // page = tmp;
            break;    
        }
    }

    return page;
}